class OggVorbis
{
	public:
		OggVorbis(const char * filename);
		int play();
		int setLooping(bool enable);
		int stop();
		~OggVorbis();
		OggVorbis();

	private:
		OggVorbis_File vorbisFile;
	
		float rate;
		u32 channels;
		u32 encoding;
		u32 nsamples;
		u32 size;
		char * data;
		int audiochannel;
		bool loop;

		size_t offset;
		
		float mix[12];
		ndspInterpType interp;

		int getOpenChannel();
};