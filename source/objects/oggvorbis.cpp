#include <shared.h>

OggVorbis::OggVorbis(const char * filename)
{
	FILE * oggFile = fopen(filename, "rb"); //Open for reading in binary mode

	if (oggFile != NULL)
	{
		if (ov_open(oggFile, &this->vorbisFile, NULL, 0) < 0) 
		{
			displayError("Ogg input does not appear to be a valid ogg vorbis file or doesn't exist.");

			return;
		}

		// Decoding Ogg Vorbis bitstream
		vorbis_info * vorbisInfo = ov_info(&this->vorbisFile, -1);

		if (vorbisInfo == NULL) 
		{
			displayError("Could not retrieve ogg audio stream information.");

			return;
		}

		this->rate = (float)vorbisInfo->rate;

		this->channels = (u32)vorbisInfo->channels;

		this->encoding = NDSP_ENCODING_PCM16;

		this->nsamples = (u32)ov_pcm_total(&this->vorbisFile, -1);

		this->size = this->nsamples * this->channels * 2; // *2 because output is PCM16 (2 bytes/sample)

		this->audiochannel = this->getOpenChannel();

		this->loop = false;

		if (linearSpaceFree() < this->size) 
		{
			displayError("Not enough linear memory available.");

			return;
		}

		this->data = (char *)linearAlloc(this->size);

		// Decoding loop
		int offset = 0;
		int endOfFile = 0;
		int currentSection;

		while (!endOfFile) {
			long ret = ov_read(&this->vorbisFile, &this->data[offset], 4096, &currentSection);

			if (ret == 0)
			{
				endOfFile = 1;
			} 
			else if (ret < 0) 
			{
				ov_clear(&this->vorbisFile);

				linearFree(this->data);

				displayError("Error in the ogg vorbis stream.");

				return;
			} 
			else 
			{
				offset += ret;
			}
		}

		linearFree(&this->vorbisFile);

		ov_clear(&this->vorbisFile);

		fclose(oggFile);

		printf("Successfully loaded %s\n", filename);
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

int OggVorbis::play()
{
	printf("Playing audio source!\n");

	if (this->audiochannel == -1) {
		displayError("No available audio channel");

		return 1;
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

	return 0;
}

int OggVorbis::stop()
{
	ndspChnWaveBufClear(this->audiochannel);

	return 0;
}

int OggVorbis::setLooping(bool enable)
{
	this->loop = enable;

	return 0;
}