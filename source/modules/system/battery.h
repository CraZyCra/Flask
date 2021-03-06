#pragma once

#include "shared.h"
#include "modules/graphics/graphics.h"
#include "modules/graphics/image.h"

class Battery
{
	public:
		Battery(float x, float y);
		~Battery();
		void Render();
		void Update(float dt);

	private:
		int GetState();

		float x;
		float y;
		int state;
		std::vector<Image *> states;
		float updateTimer = 0.5;
		bool charging = false;
};