#include "shared.h"
#include "file.h"

const char * File::InitPath(const char * path)
{
	this->fileName = path;
	this->open = false;

	//free(fullPath);

	return nullptr;
}

const char * File::Init(const char * name)
{
	char * saveDirectory = "sdmc:/3ds/data/Flask/";

	char * fullPath = (char *)malloc(strlen(saveDirectory) + strlen(name) + 1);

	strcpy(fullPath, saveDirectory);
	strcat(fullPath, name);

	return this->InitPath(fullPath);
}

bool File::IsOpen()
{
	return this->open;
}

const char * File::GetMode()
{
	if (this->mode == nullptr)
		return "File is was not opened yet";

	return this->mode;
}

bool File::Open(const char * mode)
{
	this->mode = mode;

	this->fileHandle = fopen(this->fileName, mode);

	if (this->fileHandle)
		this->open = true;

	return this->open;
}

void File::Flush()
{
	fflush(this->fileHandle);
}

void File::Write(const char * data)
{	
	if (!this->open)
		return;

	if (data != nullptr)
		fwrite(data, sizeof(char), strlen(data), this->fileHandle);
}

int File::GetSize()
{
	int size = 0;	
	int pos = 0;
	
	if (this->fileHandle == nullptr) 
		return -1;
		
	pos = ftell(this->fileHandle);

	fseek(this->fileHandle, 0, SEEK_END);

	size = ftell(this->fileHandle);

	fseek(this->fileHandle, pos, SEEK_SET);

	return size;
}

char * File::Read()
{
	char * buffer = nullptr;
	char * error = nullptr;

	if (this->fileHandle == nullptr)
	{
		if (errno == ENOENT)
			error = strdup("File not found");
		else
			error = strdup("File not open for reading");

		return error;
	}

	buffer = (char *)malloc(sizeof(char) * this->GetSize());

	fread(buffer, 1, this->GetSize(), this->fileHandle);

	buffer[this->GetSize()] = 0x0;

	return buffer;
}

void File::Close()
{
	if (!this->open)
		return;

	fclose(this->fileHandle);
}