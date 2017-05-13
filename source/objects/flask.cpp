#include "shared.h"

void Flask::Init()
{
	this->clearColor = starlight::Color(0.26f, 0.26f, 0.26f);

	this->lumaVersion = GetLumaVersion();

	auto form = std::make_shared<Form>(true);
	form->priority = 1;

	auto homeButton = std::make_shared<Button>(starlight::VRect(0, 208, 80, 32));
	homeButton->style.glyph = ThemeManager::GetAsset("graphics/home.png");
	form->touchScreen->Add(homeButton);

	auto homeForm = std::make_shared<Form>(true);
	auto packagesForm = std::make_shared<Form>(true);
	auto updatesForm = std::make_shared<Form>(true);
	auto settingsForm = std::make_shared<Form>(true);

	//make stuff
	auto banner = std::make_shared<Image>(starlight::Vector2(16, 32), "graphics/banner.png");
	auto welcome = std::make_shared<Label>(starlight::VRect(115, 50, 200, 24));
	welcome->SetFont("roboto24");
	welcome->SetText("Welcome to Flask!");

	auto createdLabel = std::make_shared<Label>(starlight::VRect(148, 80, 164, 16));
	createdLabel->SetFont("roboto16");
	createdLabel->SetText("Created by TurtleP");

	//auto thanks = std::make_shared<Label>(starlight::VRect(16, 168, 288, 176));
	//thanks->SetFont("roboto16");
	//thanks->SetText("Special Thanks:\nzetaPRIME: libstarlight");

	homeForm->touchScreen->Add(banner);
	homeForm->touchScreen->Add(welcome);
	homeForm->touchScreen->Add(createdLabel);
	//homeForm->touchScreen->Add(thanks);

	homeForm->Open();
	homeForm->Hide();

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
	packagesButton->style.glyph = ThemeManager::GetAsset("graphics/packages.png");
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
	updatesButton->style.glyph = ThemeManager::GetAsset("graphics/updates.png");
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
	settingsButton->style.glyph = ThemeManager::GetAsset("graphics/settings.png");
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
}

void Flask::CheckForUpdates()
{
	//downloadFile("https://api.github.com/repos/TurtleP/Flask/releases", "Flask.json");

	FILE * flaskJSON = fopen("sdmc:/flask/Flask.json", "rb");
	
	int flaskSize = fsize(flaskJSON);
	char * flaskBuffer = (char *)malloc(flaskSize + 1);
	fread(flaskBuffer, 1, flaskSize, flaskJSON);
	flaskBuffer[flaskSize] = '\0';

	json j = json::parse(flaskBuffer);

	std::string remoteVersion = j[0]["tag_name"].get<std::string>();

	if (strstr(this->version, remoteVersion.c_str()) == nullptr)
		this->updateAvailable = true;
	
	//downloadFile(remoteURL.c_str(), (remoteVersion + ".7z").c_str());
}

char * Flask::GetLumaVersion()
{
	FILE * armhaxbin = fopen("sdmc:/arm9loaderhax.bin", "rb");

	int size = fsize(armhaxbin);
	char * buffer = (char *)malloc(size);
	fread(buffer, 1, size, armhaxbin);
	
	char * start = (char *)memsearch((u8 *)buffer, "Luma3DS v", size, strlen("Luma3DS v"));
	*(strstr(start, "configuration")) = '\0';

	//printf("Local: %s", start);

	return start;
}

void Flask::Update()
{

}