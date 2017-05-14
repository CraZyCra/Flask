#include "shared.h"

HTTP::HTTP(char * url, char * destination, char * filename)
{
	this->url = url;
	this->destination = destination;
	this->filename = filename;

	std::vector<char *> dirPath = split(this->destination, "/");

	std::string path = std::string(dirPath[0]) + std::string("/");

	for (int i = 1; i < dirPath.size(); i++)
	{
		path += dirPath[i] + std::string("/");
		printf("Path: %s\n Folder: %s\n", path.c_str(), dirPath[i]);
	}

	this->DisableVerify();
}

HTTP::~HTTP()
{
	free(this->url);
	free(this->destination);
	free(this->filename);
	delete this->file;
}

void HTTP::Download()
{
	this->returnResult = httpcOpenContext(&this->httpContext, HTTPC_METHOD_GET, this->url, 1);
	
	if (this->returnResult != 0) 
		displayError("Failed to request url.");

	httpcAddRequestHeaderField(&httpContext, (char *)"User-Agent", (char *)"3DSFlask"); 

	this->returnResult = httpcBeginRequest(&this->httpContext);

	if (returnResult != 0) 
		displayError("Failed to begin http request");

	this->returnResult = httpcGetResponseStatusCode(&this->httpContext, &this->statusCode);

	if (this->statusCode != 200) 
		displayError("Invalid status code");

	this->buffer = (u8 *)malloc(this->bufferSize);

	if (buffer == NULL) 
		displayError("Could not create download buffer.");

	char * fullpath = (char *)mallc(strlen(this->destination) + strlen(this->filename) + 1);
	strcpy(fullpath, this->destination);
	strcat(fullpath, this->filename);

	this->file = fopen(fullpath, "wb");

	do {

		this->returnResult = httpcDownloadData(&this->httpContext, this->buffer, this->bufferSize, &this->size);

		fwrite(this->buffer, 1, this->size, this->file);

	} while (this->returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

	if (this->returnResult != 0) 
		displayError("File failed to download.");

	free(fullpath);

	fflush(this->file);

	fclose(this->file);

	httpcCloseContext(&this->httpContext);
}

void HTTP::DisableVerify()
{
	this->returnResult = httpcSetSSLOpt(&httpContext, SSLCOPT_DisableVerify);

	if (returnResult != 0) 
		displayError("Failed to Disable SSL Verification.");
}