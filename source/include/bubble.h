#pragma once

#include "wrap_graphics.h"
#include "image.h"

class Bubble
{
	public:
		Bubble(float x, float y);
		void Update(float dt);
		void Render();
		bool ShouldRemove();

	private:
		float x;
		float y;
		gfxScreen_t screen = GFX_BOTTOM;
		Image * graphic;
		bool remove = false;
};