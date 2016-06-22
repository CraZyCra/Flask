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

void downloadFile(char * url, char * filename)
{
	httpcContext httpContext;

	Result returnResult = 0;

	u8 * buffer;

	u32 statusCode;

	u32 size;

	httpcOpenContext(&httpContext, HTTPC_METHOD_GET, url, 1);
	
	httpcSetSSLOpt(&httpContext, SSLCOPT_DisableVerify);

	httpcBeginRequest(&httpContext);

	httpcGetResponseStatusCode(&httpContext, &statusCode, 0);

	if (statusCode != 200) displayError("Invalid status code");

	httpcGetDownloadSizeState(&httpContext, NULL, &size);

	buffer = (u8 *)malloc(size);

	if (buffer == NULL) displayError("Could not malloc httpc buffer");

	memset(buffer, 0, size);

	httpcDownloadData(&httpContext, buffer, size, NULL);

	printf("Making filepath\n");
	char * sdmcPath = "sdmc:/flask/";

	char * fullpath = (char *)malloc(strlen(sdmcPath) + strlen(filename) + 1);

	strcpy(fullpath, sdmcPath);

	strcat(fullpath, filename);

	FILE * downloadedFile = fopen(fullpath, "w");

	fwrite(buffer, size, 1, downloadedFile);

	fflush(downloadedFile);

	fclose(downloadedFile);

	httpcCloseContext(&httpContext);

	free(fullpath);
}

void cacheData()
{
	printf("Downloading homebrew.txt\n");
	downloadFile("https://raw.githubusercontent.com/TurtleP/Flask/master/homebrew.txt", "homebrew.txt");

	printf("Downloading icons.png\n");
	downloadFile("https://raw.githubusercontent.com/TurtleP/Flask/master/icons.png", "icons.png");

	sf2d_texture * texture = sfil_load_PNG_file("sdmc:/flask/icons.png", SF2D_PLACE_RAM);

	for (int i = 1; i < 10; i++)
	{
		Quad temp((i - 1) * 48, 0, 48, 48);
		icons->push_back(temp);
	}

    FILE * applicationFile = fopen("sdmc:/flask/homebrew.txt", "rb");
 
    long fileSize;
 
    fseek(applicationFile, 0, SEEK_END);
 
    fileSize = ftell(applicationFile);
     
    rewind(applicationFile);
 
    char * game = (char *)malloc(fileSize + 1);
 
    fread(game, fileSize, 1, applicationFile);
 
    fclose(applicationFile);
 
    std::vector<char *> newLines = split(game, "\n");
     
    std::vector<char *> data;
 	
    for (int i = 0; i < newLines.size(); i++) //1: Name, 2: Author, 3: Description, 4: Download URL, 5: Icon ID
    {
        data = split(newLines[i], ";");
 
        Application temp(24, 24 + (i * 64), data[0], data[1], data[2], i);
        temp.setDownloadURL(data[3]);

        Image * tempIcon = new Image(texture);
        temp.setIcon(tempIcon);
 
        applications->push_back(temp);
    }
}