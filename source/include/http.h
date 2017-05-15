#pragma once

class HTTP
{
	public:
		HTTP(string url, string destination, string filename);
		void Download();
		void DisableVerify();
		FILE * GetFile();

	private:
		httpcContext httpContext;
		Result returnResult = 0;
		u8 * buffer;
		u32 statusCode;
		u32 size;
		u32 bufferSize = 1024;
		
		string url;
		string destination;
		string filename;

		FILE * file;
};