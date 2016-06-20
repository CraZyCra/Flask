#include "shared.h"

Application::Application(float x, float y, const char * name, const char * author, const char * description)
{
	this->x = x;
	this->y = y;

	this->name = name;
	this->author = author;
	this->description = description;
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
	this->icon->render(this->x, this->y);

	nameFont->print(this->name, this->x + 52, this->y + 4);

	descriptionFont->print(this->description, this->x + 52, this->y + 18);
}