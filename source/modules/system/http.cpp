#include "http.h"

HTTP::HTTP(std::string url)
{
	this->url = url;
}

HTTP::HTTP(std::string url, std::string destination, std::string filename)
{
	this->url = url;
	this->destination = destination;
	this->filename = filename;
}

void HTTP::OpenContext(HTTPC_RequestMethod method, bool disableSSL)
{	
	this->returnResult = httpcOpenContext(&this->httpContext, method, this->url.c_str(), 1);

	if (this->returnResult != 0) 
		console->ThrowError("Failed to request url."); 

	if (disableSSL)
		this->DisableSSL();
}

void HTTP::DisableSSL()
{
	this->returnResult = httpcSetSSLOpt(&httpContext, SSLCOPT_DisableVerify);

	if (returnResult != 0) 
		console->ThrowError("Failed to disable SSL Verification.");
}

void HTTP::BeginRequest()
{
	this->returnResult = httpcBeginRequest(&this->httpContext);

	if (returnResult != 0) 
		console->ThrowError("Failed to begin http request");

	this->returnResult = httpcGetResponseStatusCode(&this->httpContext, &this->statusCode);

	char * newURL = nullptr;
	do
	{
			if (newURL == nullptr) 
				newURL = (char *)malloc(0x1000); // One 4K page for new URL

			if (newURL == nullptr)
				this->Close();

			httpcGetResponseHeader(&this->httpContext, "Location", newURL, 0x1000);
			this->url = newURL; // Change pointer to the url that we just learned

			httpcCloseContext(&this->httpContext); // Close this context before we try the next
	} while ((this->statusCode >= 301 && this->statusCode <= 303) || (this->statusCode >= 307 && this->statusCode <= 308));

	if (newURL == nullptr && this->statusCode != 200) 
		console->ThrowError("Invalid status code");
}

u32 HTTP::GetStatusCode()
{
	return this->statusCode;
}

void HTTP::AddRequestHeaderField(std::string field, std::string value)
{
	httpcAddRequestHeaderField(&this->httpContext, field.c_str(), value.c_str());
}

/*std::string HTTP::GetRequestHeaderField(std::string field, u32 size)
{
	static char header_buf[size];
	httpcGetResponseHeader(&this->httpContext, field.c_str(), header_buf, size);
	return string(header_buf);
}
*/

u32 HTTP::GetContentSize()
{	
	u32 tempSize = 0;
	httpcGetDownloadSizeState(&this->httpContext, nullptr, &tempSize);
	return tempSize;
}

u32 HTTP::GetSize()
{
	return this->readSize;
}

void HTTP::Download()
{
	this->buffer = (u8 *)malloc(this->bufferSize);
	u32 size = 0;

	do
	{
		this->returnResult = httpcDownloadData(&this->httpContext, this->buffer + size, this->bufferSize, &this->size);
		size += this->size;

		if (this->returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING)
		{
			this->buffer = (u8 *)realloc(this->buffer, size + this->bufferSize);
		
			if (this->buffer == nullptr)
				console->ThrowError("Buffer failed to resize");
		}
	} while (this->returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

	printf("%d\n", this->returnResult);

	if (this->returnResult != 0) 
		console->ThrowError("Data failed to download.");
	
	printf("%s\n", (char *)this->buffer);

	this->buffer = (u8 *)realloc(this->buffer, size);
	this->readSize = size;

	printf("%d\n", size);
}

std::string HTTP::GetBuffer()
{
	return std::string((char *)this->buffer);
}

void HTTP::DownloadFile()
{
	this->buffer = (u8 *)malloc(this->bufferSize);

	if (buffer == NULL) 
		console->ThrowError("Could not create download buffer.");

	this->file = fopen((this->destination + this->filename).c_str(), "wb");

	do {

		this->returnResult = httpcDownloadData(&this->httpContext, this->buffer, this->bufferSize, &this->size);

		fwrite(this->buffer, 1, this->size, this->file);

	} while (this->returnResult == (s32)HTTPC_RESULTCODE_DOWNLOADPENDING);

	if (this->returnResult != 0) 
		console->ThrowError("File failed to download.");

	fflush(this->file);

	fclose(this->file);

	this->Close();
}

void HTTP::Close()
{
	httpcCloseContext(&this->httpContext);
}