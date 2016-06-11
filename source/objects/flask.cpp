#include <shared.h>

Flask::Flask()
{
	this->bubbleGraphic = sfil_load_PNG_file("graphics/bubble.png", SF2D_PLACE_RAM);

	this->bubbles = new std::vector<Bubble>();

	this->bubbleTimer = rand() % 2 + 1;
}

void Flask::update(float dt)
{
	for (int i = 0; i < (*this->bubbles).size(); i++)
	{
		(*this->bubbles)[i].update(dt);
		if ((*this->bubbles)[i].shouldRemove() == true)
		{
			(*this->bubbles)[i].resetBubble();
		}
	}

	if ((*this->bubbles).size() < 30)
	{
		if (this->bubbleTimer > 0)
		{
			this->bubbleTimer -= dt;
		}
		else
		{	
			Bubble temp(bubbleGraphic);
			this->bubbles->push_back(temp);
			this->bubbleTimer = rand() % 2 + 1;
		}
	}
}

void Flask::render()
{
	for (int i = 0; i < (*this->bubbles).size(); i++)
	{
		(*this->bubbles)[i].render();
	}
}