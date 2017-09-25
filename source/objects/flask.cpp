#include "include/flask.h"

Flask::Flask()
{
	graphicsSetBackgroundColor(66, 165, 245);

	for (int i = 0; i < 4; i++)
		this->gui.push_back(new Button((i * 80), 208, i));

	this->gui[0]->Select(true);
	this->state = 0;

	this->wifiModule = new WiFi(2, 2);
	this->batteryModule = new Battery(374, 4);

	this->mainFont = new Font("fonts/Roboto.12");
	graphicsSetFont(this->mainFont);

	this->logo = new Texture("graphics/banner.png");

	this->clickSound = new Source("audio/cursor.ogg", "static");

	this->CheckForUpdates();
}

void Flask::Update(float dt)
{
	this->wifiModule->Update(dt);
	this->batteryModule->Update(dt);

	for (auto &bubble : this->bubbles)
	{
		bubble->Update(dt);
		if (bubble->ShouldRemove())
			this->bubbles.erase(std::remove(this->bubbles.begin(), this->bubbles.end(), bubble), this->bubbles.end());
	}

	this->bubbleTimer -= dt;
	if (this->bubbleTimer < 0)
	{
		this->bubbles.push_back(new Bubble(rand() % 320, 240));
		this->bubbleTimer = 0.15;
	}
}

void Flask::Render()
{
	graphicsSetScreen(GFX_TOP);
	this->wifiModule->Render();
	this->batteryModule->Render();

	time_t now = time(0);
	tm *ltm = localtime(&now);

	int hour = 1 + ltm->tm_hour;
	int mins = 1 + ltm->tm_min;

	std::string time = std::to_string(hour) + ":" + std::to_string(mins);

	graphicsPrint(time.c_str(), 200 - this->mainFont->GetWidth(time.c_str()) / 2, 3 + (8 - this->mainFont->GetHeight() / 2));

	graphicsSetScreen(GFX_BOTTOM);

	graphicsSetColor(255, 255, 255);

	for (auto &bubble : this->bubbles)
		bubble->Render();

	graphicsSetColor(255, 255, 255);

	if (this->state == 0)
	{
		this->logo->Render(160 - this->logo->GetWidth() / 2, 20);
		graphicsPrint("By TurtleP", 180, 84);
	}

	graphicsSetColor(33, 150, 243);
	graphicsRectangle(0, 208, 320, 32);

	for (auto &item : this->gui)
		item->Render();
}

void Flask::Touch(float x, float y)
{
	for (auto &item : this->gui)
	{
		if (item->Touch(x, y))
		{
			this->state = item->GetID();
			this->clickSound->Play();
		}
	}
}

void Flask::KeyPressed(std::string key)
{
	if (key.find("button") != std::string::npos)
	{
		if (key == "rbutton")
		{
			if (this->state + 1 < this->gui.size())
				this->clickSound->Play();

			this->state = std::min(this->state + 1, (int)this->gui.size() - 1);
		}
		else if (key == "lbutton")
		{
			if (this->state - 1 > -1) 
				this->clickSound->Play();

			this->state = std::max(this->state - 1, 0);
		}

		for (auto &item : this->gui)
		{
			if (item->GetID() != this->state)
				item->Select(false);
		}

		this->gui[this->state]->Select(true);
	}

	if (key == "start")
		QUIT_APP = true;
}

void Flask::KeyReleased(std::string key)
{

}

void Flask::LoadHomebrew()
{

}

void Flask::CheckForUpdates()
{
	HTTP * updateRequest = new HTTP("https://api.github.com/repos/TurtleP/Flask/releases");
	updateRequest->OpenContext(HTTPC_METHOD_GET, true);
	updateRequest->AddRequestHeaderField(std::string("User-Agent:"), std::string("Flask/") + this->version);
	updateRequest->BeginRequest();
	updateRequest->Download();
	updateRequest->Close();

	std::string jsonBuffer = updateRequest->GetBuffer();

	printf("%s\n", jsonBuffer.c_str());
}