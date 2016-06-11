#include <shared.h>

Flask::Flask()
{
	this->bubbleGraphic = sfil_load_PNG_file("graphics/bubble.png", SF2D_PLACE_RAM);
	this->bubbles = new std::vector<Bubble>();
}

void Flask::update(float dt)
{
	printf("Bubble vector loop\n");
	for (int i = 0; i < this->bubbles->size(); i++)
	{
		printf("Checking if should remove\n");
		if ((*this->bubbles)[i].shouldRemove() == true)
		{
			printf("Resetting bubble %d\n", i);
			(*this->bubbles)[i].resetBubble();
		}
		else
		{
			printf("Updating bubble %d\n", i);
			(*this->bubbles)[i].update(dt);
			printf("Updated\n");
		}
	}

	if (this->bubbles->size() < 30)
	{
		printf("Checking for bubble spawn\n");
		if (rand() % 10 + 1 == 1)
		{
			Bubble temp(bubbleGraphic);
			this->bubbles->push_back(temp);
		}
	}
}

void Flask::render()
{
	printf("Rednering bubbles n stuff\n");
	for (int i = 0; i < this->bubbles->size(); i++)
	{
		(*this->bubbles)[i].render();
	} 
}