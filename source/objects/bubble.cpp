#include "include/bubble.h"

Bubble::Bubble(float x, float y)
{
	this->x = x;
	this->y = y;

	std::string bubbleID = "graphics/bubbles/bubble";
	bubbleID += std::to_string(rand() % 9 + 1);
	bubbleID += ".png";

	this->graphic = new Image(bubbleID.c_str());
}

void Bubble::Update(float dt)
{
	this->y = this->y - 96 * dt;
	if (this->y + this->graphic->GetHeight() < 0)
	{
		if (this->screen == GFX_BOTTOM)
		{
			this->x += 40;
			this->y = 240;
			this->screen = GFX_TOP;
		}
		else
			this->remove = true;
	}
}

void Bubble::Render()
{
	graphicsSetScreen(this->screen);

	graphicsSetColor(100, 181, 246);

	bindTexture(this->graphic->GetTexture());
	graphicsDraw(this->graphic->GetTexture(), this->x, this->y, this->graphic->GetWidth(), this->graphic->GetHeight(), 0, 1, 1);
}

bool Bubble::ShouldRemove()
{
	return this->remove;
}