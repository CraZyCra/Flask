#include "shared.h"

Application::Application(float x, float y)
{
	this->x = x;
	this->y = y;

	this->name = "";
	this->author = "";
	this->description = "";

	sf2d_texture * downloadImage = sfil_load_PNG_file("graphics/download.png", SF2D_PLACE_RAM);
	this->downloadIcon = new Image(downloadImage);
}

void Application::setName(const char * name)
{
	strstor(this->name, name);
}

void Application::setAuthor(const char * author)
{
	strstor(this->author, author);
}

void Application::setDescription(const char * description)
{
	//strstor(this->description, description);
}

void Application::setDownloadURL(const char * url)
{
	/*if (this->downloadURL) free(this->downloadURL);

	this->downloadURL = (char *)malloc(strlen(url) + 1);

	strcpy(this->downloadURL, url);
	*/
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

	this->icon->render(this->x + 260, this->y + 12);
}