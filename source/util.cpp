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

void generateIcons(const char * url)
{
	httpcContext httpContext;

	Result returnResult = 0;

	u8 * buffer;

	u32 statusCode;

	u32 size;

	printf("Opening context.\n");
	httpcOpenContext(&httpContext, HTTPC_METHOD_GET, url, 1);
	
	printf("Disabling sslc\n");
	httpcSetSSLOpt(&httpContext, SSLCOPT_DisableVerify);

	printf("Beginning request.\n");
	httpcBeginRequest(&httpContext);

	printf("Getting status code.\n");
	httpcGetResponseStatusCode(&httpContext, &statusCode, 0);

	if (statusCode != 200) displayError("Invalid status code");

	printf("Getting download size.\n");
	httpcGetDownloadSizeState(&httpContext, NULL, &size);

	printf("Malloc'ing buffer\n");
	buffer = (u8 *)malloc(size);

	if (buffer == NULL) displayError("Could not malloc httpc buffer");

	memset(buffer, 0, size);

	printf("Downloading.\n");
	httpcDownloadData(&httpContext, buffer, size, NULL);

	printf("Preparing..\n");
	FILE * fileIcon = fopen("sdmc:/flask/icons.png", "w");

	printf("Writing..\n");
	fwrite(buffer, size, 1, fileIcon);

	printf("Flushing..\n");
	fflush(fileIcon);

	printf("Done!\n");
	fclose(fileIcon);

	printf("Closing context.\n");
	httpcCloseContext(&httpContext);
}

void cacheData()
{
	printf("Opening homebrew.txt on sdmc..\n");
	FILE * applicationFile = fopen("sdmc:/flask/homebrew.txt", "rb");

	long fileSize;

	fseek(applicationFile, 0, SEEK_END);

	fileSize = ftell(applicationFile);
  	
	rewind(applicationFile);

	char * homebrewList = (char *)malloc(fileSize + 1);

	printf("Reading data..\n");
	fread(homebrewList, fileSize, 1, applicationFile);

	fclose(applicationFile);

	printf("Making json array\n");
	/*json_value * jsonArray = json_parse(homebrewList, fileSize);

	printf("Looping json array\n");
	for (int i = 0; i < jsonArray->u.array.length; i++) //1: Name, 2: Author, 3: Description, 4: Download URL, 5: Icon URL
	{
		if (jsonArray->u.array.values[i])
		{
			Application temp(24, 22 + (i * 64), jsonArray->u.array.values[i][0], jsonArray->u.array.values[i][1], jsonArray->u.array.values[i][2]);
			temp.setDownloadURL(jsonArray->u.array.values[i][3]);

			printf("Downloading icons.\n");
			generateIcons(jsonArray->u.array.values[i][4]);

			sf2d_texture * texture = sfil_load_PNG_file("sdmc:/flask/icons.png", SF2D_PLACE_RAM);

			Image * tempIcon = new Image(texture);

			temp.setIcon(tempIcon);

			applications->push_back(temp);
		}
	}*/
}

void loadBackgroundSong(void * arg)
{
	printf("Loading bgm.ogg..\n");
	OggVorbis * backgroundMusic = new OggVorbis("audio/bgm.ogg");
	printf("Loaded.\n");
	backgroundMusic->setLooping(true);
	backgroundMusic->play();
}