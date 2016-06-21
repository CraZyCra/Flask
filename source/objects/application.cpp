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

void Application::render()
{
	this->icon->render((*icons)[this->quadID], this->x, this->y);

	nameFont->print(this->name, this->x + 52, this->y + 4);

	authorFont->print(this->author, this->x + 52, this->y + 24);
}