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