#pragma once

#include "wrap_graphics.h"
#include "crendertarget.h"
#include "button.h"
#include "wifi.h"
#include "battery.h"
#include "bubble.h"

#include "texture.h"
#include "font.h"

#include "shared.h"
#include "include/http.h"


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