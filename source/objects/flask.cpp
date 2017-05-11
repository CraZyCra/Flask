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

	CFileSeqInStream inStream;
	CFileOutStream outStream;

	FileSeqInStream_CreateVTable(&inStream);
	File_Construct(&inStream.file);

	FileOutStream_CreateVTable(&outStream);
	File_Construct(&outStream.file);

	SRes SResult;
	printf("Opening file.\n");
	if (InFile_Open(&inStream.file, "sdmc:/flask/Luma3DS.7z") != 0)
		displayError("Can not open Luma3DS.7z!");
	else
		printf("Decoding file.\n");
		SResult = Decode(&outStream.s, &inStream.s);

	printf("Done.\n");
	File_Close(&inStream.file);

	printf("Result: %d\n", SResult);
}

void Flask::CheckForUpdates()
{
	//downloadFile("https://api.github.com/repos/AuroraWright/Luma3DS/releases", "Luma.json");

	FILE * luma = fopen("sdmc:/flask/Luma.json", "rb");
	
	int lumaSize = fsize(luma);
	char * lumaBuffer = (char *)malloc(lumaSize + 1);
	fread(lumaBuffer, 1, lumaSize, luma);
	lumaBuffer[lumaSize] = '\0';

	json j = json::parse(lumaBuffer);

	std::string remoteVersion = "Luma3DS " + j[0]["tag_name"].get<std::string>();
	//std::string remoteURL = j[0]["zipball_url"];

	if (strstr(this->lumaVersion, remoteVersion.c_str()) == nullptr)
	{
		this->lumaUpdate = true;
		//downloadFile(remoteURL.c_str(), (remoteVersion + ".7z").c_str());
	}

	//printf("Remote: %s\n", remoteVersion.c_str());

	//unzOpen("sdmc:/flask/" + remoteVersion + ".zip");
	//unzFile lumaPayloadZip = unzOpen("sdmc:/flask/Luma3DS.7z");
	//if (lumaPayloadZip)
	//	printf("!");
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