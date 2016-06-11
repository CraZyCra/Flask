#include <shared.h>

Flask::Flask()
{
	this->bubbleGraphic = sfil_load_PNG_file("graphics/bubble.png", SF2D_PLACE_RAM);
}

void Flask::update(float dt)
{
	for (int i = this->bubbles.capacity(); i > 0; i--)
	{
		if (this->bubbles[i].shouldRemove())
		{
			this->bubbles[i].resetBubble();
		}
		else
		{
			this->bubbles[i].update(dt);
		}
	}

	if (this->bubbles.size() < 30)
	{
		if (rand() % 10 + 1 == 1)
		{
			Bubble temp(bubbleGraphic);
			this->bubbles.push_back(temp);
		}
	}
}

void Flask::render()
{
	for (int i = 0; i < this->bubbles.size(); i++)
	{
		this->bubbles[i].render();
	} 
}