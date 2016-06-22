#include "shared.h"

Application::Application(float x, float y, const char * name, const char * author, const char * description, int quadID)
{
	this->x = x;
	this->y = y;

	this->name = name;
	this->author = author;
	this->description = description;

	this->quadID = quadID;
}

void Application::setDownloadURL(const char * url)
{
	this->downloadURL = url;
}

void Application::setIcon(Image * icon)
{
	this->icon = icon;
}

void Application::render(float translateValue)
{
	this->icon->render((*icons)[this->quadID], this->x, floor(this->y - translateValue));

	nameFont->print(this->name, this->x + 52, floor((this->y + 4) - translateValue));

	authorFont->print(this->author, this->x + 52, floor((this->y + 24) - translateValue));
}