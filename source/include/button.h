#pragma once

#include "wrap_graphics.h"

#include "source.h"
#include "image.h"

class Button
{
	public:
		Button(float x, float y, int id);
		~Button();
		void Render();
		void Select(bool selected);
		bool Touch(float x, float y);
		int GetID();

	private:
		int x;
		int y;
		int width;
		int height;

		int id;
		bool selected;

		Image * graphic;

		bool Inside(float x, float y, float width, float height);
};