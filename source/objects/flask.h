#pragma once

#include "shared.h"

#include "modules/graphics/graphics.h"
#include "modules/graphics/crendertarget.h"
#include "modules/graphics/texture.h"
#include "modules/graphics/font.h"

#include "bubble.h"

#include "ui/button.h"

#include "modules/system/wifi.h"
#include "modules/system/battery.h"
#include "modules/system/http.h"


class Flask
{
	public:
		Flask();
		~Flask();

		void Update(float dt);
		void CheckForUpdates();
		void LoadHomebrew();
		void Render();
		void Touch(float x, float y);
		void TouchReleased(float x, float y);
		void KeyPressed(std::string key);
		void KeyReleased(std::string key);

	private:
		const char * version = "0.1";
		bool updateAvailable = false;
		//std::vector<Homebrew> homebrew;
		int selection = 0;

		std::vector<Button *> gui;
		std::vector<Bubble *> bubbles;

		WiFi * wifiModule;
		Battery * batteryModule;

		float bubbleTimer = 0.15;
		int state;

		Texture * logo;
		Source * clickSound;

		Font * mainFont;
};