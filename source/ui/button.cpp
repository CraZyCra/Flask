#include "button.h"

Button::Button(float x, float y, int id)
{
	this->x = x;
	this->y = y;

	this->width = 80;
	this->height = 32;

	this->graphic = new Image();

	std::vector<std::string> paths = {
		"graphics/ui/drawer/home.png",
		"graphics/ui/drawer/apps.png",
		"graphics/ui/drawer/updates.png",
		"graphics/ui/drawer/search.png"
	};

	if (id == 4)
		this->width = 80;

	this->graphic->Init(paths[id].c_str(), false);
	this->selected = false;
	this->id = id;
}

void Button::Render()
{
	graphicsSetColor(199, 199, 199, 255);

	if (this->selected)
	{
		graphicsSetColor(66, 165, 245);
		graphicsRectangle(this->x, this->y, this->width, this->height);

		graphicsSetColor(255, 255, 255, 255);
	}
	
	bindTexture(this->graphic->GetTexture());
	graphicsDraw(this->graphic->GetTexture(), this->x + (this->width / 2 - this->graphic->GetWidth() / 2), this->y + (this->height - this->graphic->GetWidth()) / 2, this->graphic->GetWidth(), this->graphic->GetHeight(), 0, 1, 1);

	graphicsSetColor(255, 255, 255, 255);
}

void Button::Select()
{
	if (!this->selected)
	{
		this->selected = true;
	}
}

void Button::UnSelect()
{
	if (this->selected)
		this->selected = false;
}

bool Button::Touch(float x, float y)
{
	this->selected = this->Inside(x, y, 1, 1);

	if (this->selected)
		return true;
	return false;
}

int Button::GetID()
{
	return this->id;
}

bool Button::Inside(float x, float y, float width, float height)
{
	return x > this->x && x < this->x + this->width && y > this->y && y < this->y + this->height;
}