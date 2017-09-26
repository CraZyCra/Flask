#pragma once

#include "shared.h"
#include "modules/graphics/graphics.h"
#include "modules/graphics/image.h"

class WiFi
{
	public:
		WiFi(float x, float y);
		~WiFi();
		void Render();
		void Update(float dt);

	private:
		int GetState();
	
		float x;
		float y;

		std::vector<Image *> states;
		int state;

		float updateTimer = 0.5;;
};