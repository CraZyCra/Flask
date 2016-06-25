#include "shared.h"

Application::Application(float x, float y)
{
	this->x = x;
	this->y = y;

	this->name = "";
	this->author = "";
	this->description = "";
}

void Application::setName(const char * name)
{
	if (this->name) free(this->name);

	this->name = (char *)malloc(strlen(name) + 1);

	strcpy(this->name, name);
}

void Application::setAuthor(const char * author)
{
	if (this->author) free(this->author);

	this->author = (char *)malloc(strlen(author) + 1);

	strcpy(this->author, author);
}

void Application::setDescription(const char * description)
{
	//strstor(this->description, description);
}

void Application::setDownloadURL(const char * url)
{
	if (this->downloadURL) free(this->downloadURL);

	this->downloadURL = (char *)malloc(strlen(url) + 1);

	strcpy(this->downloadURL, url);
}

void Application::setIcon(Image * icon)
{
	this->icon = icon;
}

void Application::render(float translateValue)
{
	this->icon->render(this->x, ceil(this->y - translateValue));

	nameFont->print(this->name, this->x + 52, ceil((this->y + 4) - translateValue));

	authorFont->print(this->author, this->x + 52, ceil((this->y + 24) - translateValue));
}