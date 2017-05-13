float deltaStep();

void cacheData();

void downloadFile(char * url, char * filename);

int fsize(FILE * file);

void strstor(char * destination, const char * source);

u8 * memsearch(u8 * startPos, const void * pattern, u32 size, u32 patternSize);