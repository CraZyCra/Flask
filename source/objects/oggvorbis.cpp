#include "shared.h"

OggVorbis::OggVorbis(const char * filename)
{
	FILE * oggFile = fopen(filename, "rb"); //Open for reading in binary mode
	OggVorbis_File vorbisFile;

	if (oggFile != NULL)
	{
		this->mode = mode;
		
		for (int i=0; i < 12; i++) 
		{
			this->mix[i] = 1.0f;
		}

		this->interp = NDSP_INTERP_LINEAR;

		if (ov_open(oggFile, &vorbisFile, NULL, 0) < 0) 
		{
			displayError("Ogg input does not appear to be a valid ogg vorbis file or doesn't exist.");

			return;
		}

		vorbis_info * vorbisInfo = ov_info(&vorbisFile, -1);

		if (vorbisInfo == NULL) 
		{
			displayError("Could not retrieve ogg audio stream information.");

			return;
		}

		this->rate = (float)vorbisInfo->rate;

		this->channels = (u32)vorbisInfo->channels;

		this->encoding = NDSP_ENCODING_PCM16;

		this->nsamples = (u32)ov_pcm_total(&vorbisFile, -1);

		this->size = this->nsamples * this->channels * 2; // *2 because output is PCM16 (2 bytes/sample)

		this->audiochannel = this->getOpenChannel();

		this->loop = false;

		if (linearSpaceFree() < this->size) 
		{
			displayError("Not enough linear memory available.");

			return;
		}

		this->data = (char *)linearAlloc(this->size);

		int offset = 0;
		int endOfFile = 0;
		int currentSection;

		while (!endOfFile) {

			long ret = ov_read(&vorbisFile, &this->data[offset], 4096, &currentSection);

			if (ret == 0)
			{
				endOfFile = 1;
			} 
			else if (ret < 0) 
			{
				ov_clear(&vorbisFile);

				linearFree(this->data);

				displayError("Error in the ogg vorbis stream.");

				return;
			} 
			else 
			{
				offset += ret;
			}
		}

		ov_clear(&vorbisFile);

		fclose(oggFile);
	}
	else
	{
		displayError("File does not exist.");
	}
}

OggVorbis::~OggVorbis()
{
	ndspChnWaveBufClear(this->audiochannel);

	linearFree(this->data);

	channelList[this->audiochannel] = false;
}

int OggVorbis::getOpenChannel()
{
	for (int i = 0; i <= 23; i++) 
	{
		if (!channelList[i]) 
		{
			channelList[i] = true;

			return i;
		}
	}

	return -1;
}

void OggVorbis::play()
{
	if (this->audiochannel == -1) {
		displayError("No available audio channel");
	}

	ndspChnWaveBufClear(this->audiochannel);

	ndspChnReset(this->audiochannel);

	ndspChnInitParams(this->audiochannel);

	ndspChnSetMix(this->audiochannel, this->mix);

	ndspChnSetInterp(this->audiochannel, this->interp);

	ndspChnSetRate(this->audiochannel, this->rate);

	ndspChnSetFormat(this->audiochannel, NDSP_CHANNELS(this->channels) | NDSP_ENCODING(this->encoding));

	ndspWaveBuf * waveBuf = (ndspWaveBuf *)calloc(1, sizeof(ndspWaveBuf));

	waveBuf->data_vaddr = this->data;

	waveBuf->nsamples = this->nsamples;

	waveBuf->looping = this->loop;

	DSP_FlushDataCache((u32 *)this->data, this->size);

	ndspChnWaveBufAdd(this->audiochannel, waveBuf);
}

void OggVorbis::stop()
{
	ndspChnWaveBufClear(this->audiochannel);
}

void OggVorbis::setLooping(bool enable)
{
	this->loop = enable;
}

void OggVorbis::setVolume(float volume)
{
	if (volume > 1) volume = 1;

	if (volume < 0) volume = 0;

	for (int i = 0; i <= 3; i++)
	{
		this->mix[i] = volume;
	}

	ndspChnSetMix(this->audiochannel, this->mix);
}