#pragma once

#include "shared.h"

class HTTP
{
	public:
		HTTP(std::string url, std::string destination, std::string filename);
		HTTP(std::string url);
	
		void OpenContext(HTTPC_RequestMethod method, bool disableSSL);
		
		void DisableSSL();
		
		void BeginRequest();
		
		void AddRequestHeaderField(std::string field, std::string value);
		//std::string GetRequestHeaderField(std::string field, u32 size);
		u32 GetContentSize();
		u32 GetStatusCode();

		void Download();
		void DownloadFile();
		
		void Close();
	
		FILE * GetFile();
		std::string GetBuffer();
		u32 GetSize();

	private:
		httpcContext httpContext;
		Result returnResult = 0;
		u8 * buffer;
		u32 statusCode;
		u32 size = 0;
		u32 readSize = 0;
		u32 bufferSize = 1024;
		
		std::string url;
		std::string destination;
		std::string filename;

		FILE * file;
};