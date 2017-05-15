#pragma once

#include "starlight/Application.h"
#include "starlight/ThemeManager.h"

#include "starlight/ui/ScrollField.h"
#include "starlight/ui/DebugConsole.h"

#include "starlight/InputManager.h"

using starlight::Application;


using starlight::ui::DebugConsole;
using starlight::ui::ScrollField;

using starlight::InputManager;
using starlight::ThemeManager;

class Flask : public Application
{
	public:
		Flask() : Application("Flask") {}
		~Flask() override = default;

		void Init() override;
		void Update() override;
		void CheckForUpdates();
		void LoadHomebrew(std::shared_ptr<starlight::ui::Form>);

	private:
		const char * version = "0.1";
		bool updateAvailable = false;
};