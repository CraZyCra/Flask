#pragma once

#include "modules/graphics/graphics.h"
#include "modules/graphics/image.h"
#include "modules/audio/source.h"

class Button
{
	public:
		Button(float x, float y, int id);
		~Button();
		void Render();

		void UnSelect();
		void Select();

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