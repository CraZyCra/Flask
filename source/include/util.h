#include "7z.h"
#include "7zFile.h"
#include "LzmaDec.h"
#include "Alloc.h"

float deltaStep();

void cacheData();

void downloadFile(char * url, char * filename);

int fsize(FILE * file);

void strstor(char * destination, const char * source);

u8 * memsearch(u8 * startPos, const void * pattern, u32 size, u32 patternSize);

SRes Decode(ISeqOutStream *outStream, ISeqInStream *inStream);

SRes Decode2(CLzmaDec *state, ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 unpackSize);