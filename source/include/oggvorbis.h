#pragma once

class OggVorbis
{
	public:
		OggVorbis(const char * filename, const char * mode);
		void play();
		void setLooping(bool enable);
		void stop();
		~OggVorbis();
		OggVorbis();

	private:
		float rate;
		u32 channels;
		u32 encoding;
		u32 nsamples;
		u32 size;
		char * data;
		int audiochannel;
		bool loop;
		
		float mix[12];
		ndspInterpType interp;
		const char * mode;

		int getOpenChannel();
};