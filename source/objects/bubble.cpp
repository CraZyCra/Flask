#include <shared.h>

Bubble::Bubble(sf2d_texture * texture)
{
	this->graphic = texture;
	
	this->x = rand() % 320 + 40;
	this->y = 240;

	this->width = 40;
	this->height = 40;	

	this->currentScreen = GFX_BOTTOM;
	this->remove = false;
}

void Bubble::update(float dt)
{
	this->y = this->y - 60 * dt;
	if (this->y + this->height < 0)
	{
		if (this->currentScreen == GFX_BOTTOM)
		{
			this->currentScreen = GFX_TOP;
			this->y = 240;
			this->x += 40;
		}
		else
		{
			this->remove = true;
		}	
	}
}

void Bubble::render()
{
	setScreen(this->currentScreen);
	draw(this->graphic, this->x, this->y);
}

void Bubble::resetBubble()
{
	this->x = rand() % 320 + 40;
	this->y = 240;

	this->currentScreen = GFX_BOTTOM;
	this->remove = false;
}

bool Bubble::shouldRemove()
{
	return this->remove;
}