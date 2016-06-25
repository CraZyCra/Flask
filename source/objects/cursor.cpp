#include "shared.h"

Cursor::Cursor()
{
	this->x = 20;
	this->y = 20;

	this->width = 280;
	this->height = 56;

	this->timer = 0;
	this->sineValue = 1;
}

void Cursor::update(float dt)
{
	this->timer = this->timer + 0.5 * dt;
	this->sineValue = abs(sin(this->timer * M_PI) / 2 ) + 0.5;
}

void Cursor::render(float translateValue)
{
	if (sf2d_get_current_screen() == getCurrentScreen()) 
	{
		setColor(41, 105, 176, 160 * this->sineValue);

		sf2d_draw_rectangle(this->x, ceil(this->y - translateValue), this->width, this->height, getCurrentColor());

		setColor(255, 255, 255, 255);
	}
}

void Cursor::setPosition(int selection)
{
	this->y = 20 + (selection * 64);
}