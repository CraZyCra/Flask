#include "shared.h"

std::vector<char *> split(char * string, char * delim)
{
	std::vector<char *> array;

	char * token = strtok(string, delim);

	while (token != NULL)
	{
		array.push_back(token);

		token = strtok(NULL, delim);
	}

	return array;
}

int fsize(FILE * file)
{
	int size;
	
	int pos = ftell(file);

	fseek(file, 0, SEEK_END);

	size = ftell(file);

	fseek(file, pos, SEEK_SET);

	return size;
}

u8 * memsearch(u8 * startPos, const void * pattern, u32 size, u32 patternSize)
{
	const u8 *patternc = (const u8 *)pattern;
	u32 table[256];

	//Preprocessing
	for(u32 i = 0; i < 256; i++)
		table[i] = patternSize;
	for(u32 i = 0; i < patternSize - 1; i++)
		table[patternc[i]] = patternSize - i - 1;

	//Searching
	u32 j = 0;
	while(j <= size - patternSize)
	{
		u8 c = startPos[j + patternSize - 1];
		if(patternc[patternSize - 1] == c && memcmp(pattern, startPos + j, patternSize - 1) == 0)
			return startPos + j;
		j += table[c];
	}

	return NULL;
}

void downloadFile(char * url, char * filename)
{
	httpcContext httpContext;

	Result returnResult = 0;

	u8 * buffer;

	u32 statusCode;

	u32 size;

	u32 bufferSize = 1024;

	returnResult = httpcOpenContext(&httpContext, HTTPC_METHOD_GET, url, 1);
	
	if (returnResult != 0) displayError("Failed to request url.");

	returnResult = httpcSetSSLOpt(&httpContext, SSLCOPT_DisableVerify);

	if (returnResult != 0) displayError("Failed to Disable SSL Verification.");

	char httpHeaderField[20];

	strcpy(httpHeaderField, "Flask/");
	strcat(httpHeaderField, flaskVersion);

	httpcAddRequestHeaderField(&httpContext, (char *)"User-Agent", httpHeaderField); 

	returnResult = httpcBeginRequest(&httpContext);

	if (returnResult != 0) displayError("Failed to begin http:C request");

	returnResult = httpcGetResponseStatusCode(&httpContext, &statusCode);

	if (statusCode != 200) displayError("Invalid status code");

	buffer = (u8 *)malloc(bufferSize);

	if (buffer == NULL) displayError("Could not malloc httpc buffer.");

	char * sdmcPath = "sdmc:/flask/";

	char * fullpath = (char *)malloc(strlen(sdmcPath) + strlen(filename) + 1);

	strcpy(fullpath, sdmcPath);

	strcat(fullpath, filename);

	FILE * downloadedFile = fopen(fullpath, "w+");

	if (downloadedFile != NULL)
	{
		remove(fullpath);
	}

	do {
		
		returnResult = httpcDownloadData(&httpContext, buffer, bufferSize, &size);

		fwrite(buffer, 1, size, downloadedFile);

	} while (returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);


	if (returnResult != 0) displayError("Downloading file failed somehow");

	fflush(downloadedFile);

	fclose(downloadedFile);

	httpcCloseContext(&httpContext);
	
	free(buffer);

	free(fullpath);
}

#define IN_BUF_SIZE (1 << 16)
#define OUT_BUF_SIZE (1 << 16)

SRes Decode(ISeqOutStream *outStream, ISeqInStream *inStream)
{
  UInt64 unpackSize;
  int i;
  SRes res = 0;

  CLzmaDec state;

  /* header: 5 bytes of LZMA properties and 8 bytes of uncompressed size */
  unsigned char header[LZMA_PROPS_SIZE + 8];

  /* Read and parse header */

  RINOK(SeqInStream_Read(inStream, header, sizeof(header)));

  unpackSize = 0;
  for (i = 0; i < 8; i++)
	unpackSize += (UInt64)header[LZMA_PROPS_SIZE + i] << (i * 8);

  LzmaDec_Construct(&state);
  RINOK(LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &g_Alloc));
  res = Decode2(&state, outStream, inStream, unpackSize);
  LzmaDec_Free(&state, &g_Alloc);
  return res;
}

SRes Decode2(CLzmaDec *state, ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 unpackSize)
{
  int thereIsSize = (unpackSize != (UInt64)(Int64)-1);
  Byte inBuf[IN_BUF_SIZE];
  Byte outBuf[OUT_BUF_SIZE];
  size_t inPos = 0, inSize = 0, outPos = 0;
  LzmaDec_Init(state);
  for (;;)
  {
	if (inPos == inSize)
	{
	  inSize = IN_BUF_SIZE;
	  RINOK(inStream->Read(inStream, inBuf, &inSize));
	  inPos = 0;
	}
	{
	  SRes res;
	  SizeT inProcessed = inSize - inPos;
	  SizeT outProcessed = OUT_BUF_SIZE - outPos;
	  ELzmaFinishMode finishMode = LZMA_FINISH_ANY;
	  ELzmaStatus status;
	  if (thereIsSize && outProcessed > unpackSize)
	  {
		outProcessed = (SizeT)unpackSize;
		finishMode = LZMA_FINISH_END;
	  }
	  
	  res = LzmaDec_DecodeToBuf(state, outBuf + outPos, &outProcessed,
		inBuf + inPos, &inProcessed, finishMode, &status);
	  inPos += inProcessed;
	  outPos += outProcessed;
	  unpackSize -= outProcessed;
	  
	  if (outStream)
		if (outStream->Write(outStream, outBuf, outPos) != outPos)
		  return SZ_ERROR_WRITE;
		
	  outPos = 0;
	  
	  if (res != SZ_OK || (thereIsSize && unpackSize == 0))
		return res;
	  
	  if (inProcessed == 0 && outProcessed == 0)
	  {
		if (thereIsSize || status != LZMA_STATUS_FINISHED_WITH_MARK)
		  return SZ_ERROR_DATA;
		return res;
	  }
	}
  }
}