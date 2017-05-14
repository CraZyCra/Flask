#pragma once

#include "starlight/Application.h"
#include "starlight/ThemeManager.h"

#include "starlight/ui/Image.h"
#include "starlight/ui/Button.h"
#include "starlight/ui/Form.h"
#include "starlight/ui/Label.h"
#include "starlight/ui/ScrollField.h"
#include "starlight/ui/DebugConsole.h"

#include "starlight/InputManager.h"
#include "starlight/_incLib/json.hpp"

using starlight::Application;

using starlight::ui::Image;
using starlight::ui::Button;
using starlight::ui::Form;
using starlight::ui::Label;
using starlight::ui::DebugConsole;
using starlight::ui::ScrollField;

using starlight::InputManager;
using starlight::ThemeManager;
using nlohmann::json;

class Flask : public Application
{
	public:
		Flask() : Application("Flask") {}
		~Flask() override = default;

		void Init() override;
		void Update() override;
		
		void CheckForUpdates();

	private:
		const char * version = "0.1";
		bool updateAvailable = false;
};