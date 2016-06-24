#include "shared.h"
#include <jansson.h>

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

	/*if (size == fsize("sdmc:/flask/flask.json"))
	{
		httpcCloseContext(&httpContext);
		return;
	}*/

	buffer = (u8 *)malloc(size);

	if (buffer == NULL) displayError("Could not malloc httpc buffer");

	memset(buffer, 0, size);

	httpcDownloadData(&httpContext, buffer, size, NULL);

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
	downloadFile("https://3ds.intherack.com/flask/list", "flask.json");

    json_t * flaskJson = json_load_file("sdmc:/flask/flask.json", JSON_DECODE_ANY, NULL);
 	
 	size_t arrayIndex;
	json_t * arrayValue;

	const char * objectKey;
	json_t * objectValue;

	json_array_foreach(flaskJson, arrayIndex, arrayValue) {
	    json_t * jsonObject = json_array_get(flaskJson, arrayIndex);

	    json_object_foreach(jsonObject, objectKey, objectValue) {
	  		Application temp(24, 24 + (arrayIndex * 64));

	  		if (strcmp(objectKey, "name") == 0)
	  		{
	  			temp.setName(json_string_value(objectValue));
	  		}
	  		else if (strcmp(objectKey, "author") == 0)
	  		{
	  			temp.setAuthor(json_string_value(objectValue));	
	  		}
	  		else if (strcmp(objectKey, "description") == 0)
	  		{
	  			temp.setDescription(json_string_value(objectValue));
	  		}
	  		else if (strcmp(objectKey, "url") == 0)
	  		{
	  			temp.setDownloadURL(json_string_value(objectValue));
	  		}

	  		//because we're not doing icons yet with cia stuff. .
	  		sf2d_texture * noneImage = sfil_load_PNG_file("graphics/none.png", SF2D_PLACE_RAM);
	  		Image * noneIcon = new Image(noneImage);

	  		temp.setIcon(noneIcon);

	  		applications->push_back(temp);
		}
	}
}

int fsize(const char * file)
{
	struct stat st;

  	stat(file, &st);
  
  	return st.st_size;
}

void strstor(char * destination, const char * source)
{
	if (destination) free(destination);

	destination = (char *)malloc(strlen(source) + 1);

	strcpy(destination, source);
}