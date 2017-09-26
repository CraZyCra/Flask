#include "wifi.h"

WiFi::WiFi(float x, float y)
{
	this->x = x;
	this->y = y;

	this->states = {new Image("graphics/ui/wifi/no-wifi.png"), new Image("graphics/ui/wifi/wifi-scan.png"), new Image("graphics/ui/wifi/wifi.png")};

	this->state = 1;
}

void WiFi::Update(float dt)
{
	this->updateTimer = this->updateTimer - dt;
	if (this->updateTimer < 0)
	{
		this->state = this->GetState();
		this->updateTimer = 0.5;
	}
}

void WiFi::Render()
{
	graphicsSetColor(255, 255, 255);
	bindTexture(this->states[this->state]->GetTexture());
	graphicsDraw(this->states[this->state]->GetTexture(), this->x, this->y, this->states[this->state]->GetWidth(), this->states[this->state]->GetHeight(), 0, 1, 1);
}

int WiFi::GetState()
{
	int strength = osGetWifiStrength();

	if (strength > 0)
		return 2;
	else if (strength == 0)
		return 0;
	return 0;
}