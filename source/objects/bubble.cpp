#include <shared.h>

Bubble::Bubble(sf2d_texture * texture)
{
	this->graphic = texture;
	
	this->x = rand() % 320 + 40;
	this->y = 240;

	this->width = 40;
	this->height = 40;	

	this->currentScreen = "bottom";
	this->remove = false;
}

void Bubble::update(float dt)
{
	this->y = this->y - dt;
	if (this->currentScreen == "bottom") 
	{
		if (this->y + this->height < 0)
		{
			this->currentScreen = "top";
		}
	}
	else
	{
		this->remove = true;
	}
}

void Bubble::render()
{
	setScreen(this->currentScreen);
	sf2d_draw_texture_blend(this->graphic, this->x, this->y, getCurrentColor());
}

void Bubble::resetBubble()
{
	this->x = rand() % 320 + 40;
	this->y = 240;

	this->currentScreen = "bottom";
	this->remove = false;
}

bool Bubble::shouldRemove()
{
	return this->remove;
}