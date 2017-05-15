#include "shared.h"

HTTP::HTTP(string url, string destination, string filename)
{
	this->url = url;
	this->destination = destination;
	this->filename = filename;
}

void HTTP::Download()
{
	this->returnResult = httpcOpenContext(&this->httpContext, HTTPC_METHOD_GET, this->url.c_str(), 1);
	
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

	this->file = fopen((this->destination + this->filename).c_str(), "wb");

	do {

		this->returnResult = httpcDownloadData(&this->httpContext, this->buffer, this->bufferSize, &this->size);

		fwrite(this->buffer, 1, this->size, this->file);

	} while (this->returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

	if (this->returnResult != 0) 
		displayError("File failed to download.");

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