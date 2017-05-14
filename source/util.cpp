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

	strcpy(httpHeaderField, "3DSFlask");

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