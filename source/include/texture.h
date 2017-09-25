#pragma once

#include "wrap_graphics.h"
#include "image.h"

class Texture
{
	public:
		Texture(const char * path);
		void Render(float x, float y);
		int GetWidth();
		int GetHeight();

	private:
		int width;
		int height;

		Image * graphic;
};