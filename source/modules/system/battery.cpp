#include "battery.h"

Battery::Battery(float x, float y)
{
	this->x = x;
	this->y = y;

	for (int i = 0; i < 5; i++)
	{
		std::string tmp = "graphics/ui/battery/battery-";
		tmp += std::to_string(i) + ".png";

		this->states.push_back(new Image(tmp.c_str()));
	}

	this->states.push_back(new Image("graphics/ui/battery/charging.png"));
	this->state = 4;
}

void Battery::Update(float dt)
{
	this->updateTimer = this->updateTimer - dt;
	if (this->updateTimer < 0)
	{
		this->state = this->GetState();
		this->updateTimer = 0.5;
	}
}

void Battery::Render()
{
	graphicsSetColor(255, 255, 255);
	bindTexture(this->states[this->state]->GetTexture());
	graphicsDraw(this->states[this->state]->GetTexture(), this->x, this->y, this->states[this->state]->GetWidth(), this->states[this->state]->GetHeight(), 0, 1, 1);

	if (this->charging)
	{
		bindTexture(this->states[5]->GetTexture());
		graphicsDraw(this->states[5]->GetTexture(), this->x + this->states[this->state]->GetWidth() / 2 - 4, this->y + this->states[this->state]->GetHeight() / 2 - 4, this->states[5]->GetWidth(), this->states[5]->GetHeight(), 0, 1, 1);
	}
}

int Battery::GetState() //0-5
{
	u8 batteryLevel;
	PTMU_GetBatteryLevel(&batteryLevel);

	u8 batteryStateBool;
	PTMU_GetBatteryChargeState(&batteryStateBool);
	
	this->charging = false;
	if (batteryStateBool == 1)
		this->charging = true;

	if (batteryLevel > 4)
		return 4;
	return batteryLevel;
}