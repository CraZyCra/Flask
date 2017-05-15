#include "shared.h"

void Flask::Init()
{
	this->clearColor = starlight::Color(0.26f, 0.26f, 0.26f);

	auto form = std::make_shared<Form>(true);
	form->priority = 1;

	auto homeButton = std::make_shared<Button>(starlight::VRect(0, 208, 80, 32));
	homeButton->style.glyph = ThemeManager::GetAsset("romfs:/graphics/home.png");
	form->touchScreen->Add(homeButton);

	auto homeForm = std::make_shared<Form>(true);
	auto packagesForm = std::make_shared<Form>(true);
	auto updatesForm = std::make_shared<Form>(true);
	auto settingsForm = std::make_shared<Form>(true);

	//make stuff
	auto banner = std::make_shared<Image>(starlight::Vector2(16, 32), "romfs:/graphics/banner.png");
	auto welcome = std::make_shared<Label>(starlight::VRect(115, 50, 200, 24));
	welcome->SetFont("romfs:/fonts/roboto.24");
	welcome->SetText("Welcome to Flask!");

	auto createdLabel = std::make_shared<Label>(starlight::VRect(148, 80, 164, 16));
	createdLabel->SetFont("romfs:/fonts/roboto.16");
	createdLabel->SetText("Created by TurtleP");

	homeForm->touchScreen->Add(banner);
	homeForm->touchScreen->Add(welcome);
	homeForm->touchScreen->Add(createdLabel);

	homeForm->Open();

	auto container = std::make_shared<ScrollField>(starlight::VRect(0, 0, 320, 240));
	packagesForm->touchScreen->Add(container);

	packagesForm->Open();
	packagesForm->Hide();

	updatesForm->Open();
	updatesForm->Hide();

	settingsForm->Open();
	settingsForm->Hide();


	homeButton->eOnTap = [homeForm, packagesForm, updatesForm, settingsForm](auto& btn)
	{
		packagesForm->Hide();
		updatesForm->Hide();
		settingsForm->Hide();
		if (!homeForm->IsVisible())
			homeForm->Show();
	};

	auto packagesButton = std::make_shared<Button>(starlight::VRect(80, 208, 80, 32));
	packagesButton->style.glyph = ThemeManager::GetAsset("romfs:/graphics/packages.png");
	packagesButton->eOnTap = [homeForm, packagesForm, updatesForm, settingsForm](auto& btn) 
	{
		homeForm->Hide();
		updatesForm->Hide();
		settingsForm->Hide();
		if (!packagesForm->IsVisible())
			packagesForm->Show();
	};
	form->touchScreen->Add(packagesButton);

	auto updatesButton = std::make_shared<Button>(starlight::VRect(160, 208, 80, 32));
	updatesButton->style.glyph = ThemeManager::GetAsset("romfs:/graphics/updates.png");
	updatesButton->eOnTap = [homeForm, packagesForm, updatesForm, settingsForm](auto& btn)
	{
		homeForm->Hide();
		packagesForm->Hide();
		settingsForm->Hide();
		if (!updatesForm->IsVisible())
			updatesForm->Show();
	};
	form->touchScreen->Add(updatesButton);

	auto settingsButton = std::make_shared<Button>(starlight::VRect(240, 208, 80, 32));
	settingsButton->style.glyph = ThemeManager::GetAsset("romfs:/graphics/settings.png");
	settingsButton->eOnTap = [homeForm, packagesForm, updatesForm, settingsForm](auto& btn)
	{
		homeForm->Hide();
		packagesForm->Hide();
		updatesForm->Hide();
		if (!settingsForm->IsVisible())
			settingsForm->Show();
	};
	form->touchScreen->Add(settingsButton);

	auto debug = std::make_shared<DebugConsole>(starlight::VRect(0, 0, 400, 240));
	form->topScreen->Add(debug);
	debug->Start();

	form->Open();

	this->CheckForUpdates();
	this->LoadHomebrew(packagesForm);

	//printf("Flask Version: %s\n", this->version);
	//printf("Update Available: %d\n", this->updateAvailable);
}

void Flask::LoadHomebrew(std::shared_ptr<starlight::ui::Form> form)
{
	//TODO: Change URL when needed!
	//HTTP * appHTTP = new HTTP("https://api.github.com/repos/TurtleP/Flask/releases", "sdmc:/flask/", "app.json");
	
	/*
	appHTTP->DisableVerify();
	appHTTP->Download();
	*/
	
	ifstream appFile("sdmc:/flask/app.json");
	
	json appJSON;
	appJSON << appFile;

	//delete appHTTP;
	int i = 0;
	for (auto it = appJSON.begin(); it != appJSON.end(); it++)
	{
		if (it.value().is_object())
			Homebrew(form, i, it.key(), it.value());
		i++;
	}
}

void Flask::CheckForUpdates()
{
	HTTP * test = new HTTP("https://api.github.com/repos/TurtleP/Flask/releases", "sdmc:/flask/", "flask.json");
	
	/*
	test->DisableVerify();
	test->Download();
	*/
	
	ifstream flaskFile("sdmc:/flask/flask.json");

	json flaskJSON;
	flaskJSON << flaskFile;

	string remoteVersion = flaskJSON[0]["tag_name"];

	if (strstr(this->version, remoteVersion.c_str()) == nullptr)
		this->updateAvailable = true;
	
	//delete test;

	//printf("Remote: %s\n", remoteVersion.c_str());
}

void Flask::Update()
{

}