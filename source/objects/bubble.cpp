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
	printf("Moving y coordinate\n");
	this->y = this->y - dt;

	printf("Checking current screen\n");
	if (this->currentScreen == "bottom") 
	{
		printf("Checking to move to top screen\n");
		if (this->y + this->height < 0)
		{
			printf("Moved\n");
			this->currentScreen = "top";
		}
	}
	else
	{
		printf("Resetting bubble\n");
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