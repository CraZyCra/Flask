#include "shared.h"

Flask::Flask()
{
	this->bubbleTexture = sfil_load_PNG_file("graphics/bubble.png", SF2D_PLACE_RAM);
	this->wifiTexture = sfil_load_PNG_file("graphics/wifi.png", SF2D_PLACE_RAM);
	this->batteryTexture = sfil_load_PNG_file("graphics/battery.png", SF2D_PLACE_RAM);
	this->listTexture = sfil_load_PNG_file("graphics/list.png", SF2D_PLACE_RAM);
	this->updateTexture = sfil_load_PNG_file("graphics/updates.png", SF2D_PLACE_RAM);
	this->searchTexture = sfil_load_PNG_file("graphics/search.png", SF2D_PLACE_RAM);

	this->bubbles = new std::vector<Bubble>();

	this->batteryQuads = new std::vector<Quad>();

	for (int i = 1; i < 6; i++)
	{
		Quad temp((i - 1) * 16, 0, 16, 9);
		this->batteryQuads->push_back(temp);
	}

	this->bubbleTimer = rand() % 2 + 1;

	this->wifiSignal = new Image(this->wifiTexture);
	this->batteryDisplay = new Image(this->batteryTexture);
	
	this->listDisplay = new Image(this->listTexture);
	this->updateDisplay = new Image(this->updateTexture);
	this->searchDisplay = new Image(this->searchTexture);

	this->cursorSound = new OggVorbis("audio/cursor.ogg");

	this->cursor = new Cursor();

	this->currentHomebrew = 0;
	this->smoothScroll = 0;
}

void Flask::update(float dt)
{
	for (int i = 0; i < (*this->bubbles).size(); i++)
	{
		(*this->bubbles)[i].update(dt);
		if ((*this->bubbles)[i].shouldRemove() == true)
		{
			(*this->bubbles)[i].resetBubble();
		}
	}

	if ((*this->bubbles).size() < 30)
	{
		if (this->bubbleTimer > 0)
		{
			this->bubbleTimer -= dt;
		}
		else
		{	
			Bubble temp(this->bubbleTexture);
			this->bubbles->push_back(temp);
			this->bubbleTimer = rand() % 2 + 1;
		}
	}

	this->cursor->update(dt);

	if (this->currentHomebrew < applications->size() - 2)
	{
		smoothScroll = smoothScroll + ((this->currentHomebrew * 64) - this->smoothScroll) * SCROLLRATE * dt;
	}
	else
	{
		smoothScroll = smoothScroll + (((applications->size() - 3) * 64) - this->smoothScroll) * SCROLLRATE * dt;
	}
}

void Flask::render()
{	
	for (int i = 0; i < (*this->bubbles).size(); i++)
	{
		if ((*this->bubbles)[i].getZOrder() == 0)
		{
			(*this->bubbles)[i].render();
		}
	}

	setScreen(GFX_TOP);

	time_t t = time(NULL);
    const char * currentTime = ctime(&t);
	
	descriptionFont->print(currentTime, 200 - descriptionFont->getWidth(currentTime) / 2, -2);

	u8 batteryQuadi;
	PTMU_GetBatteryLevel(&batteryQuadi);

	this->batteryDisplay->render((*this->batteryQuads)[batteryQuadi], 382, 5.5);

	this->wifiSignal->render(3, 0);

	setScreen(GFX_BOTTOM);

	this->cursor->render();

	setColor(255, 255, 255);

	push();

	translate(0, -this->smoothScroll);

	for (int i = 0; i < applications->size(); i++)
	{	
		setScissor(24, 24, 272, 192);
		
		(*applications)[i].render();

		setScissor(NULL, NULL, NULL, NULL);
	}

	pop();

	setColor(255, 255, 255);
	this->listDisplay->render(320 * 1/4 - 8, 220);

	setColor(117, 112, 107);
	this->updateDisplay->render(320 * 1/2 - 8, 220);

	setColor(117, 112, 107);
	this->searchDisplay->render(320 * 3/4 - 8, 220);

	setColor(255, 255, 255);

	for (int i = 0; i < (*this->bubbles).size(); i++)
	{
		if ((*this->bubbles)[i].getZOrder() == 1)
		{
			(*this->bubbles)[i].render();
		}
	}
}

void Flask::keyPressed(u32 key)
{
	if (key & KEY_DOWN)
	{
		if (this->currentHomebrew < applications->size() - 1)
		{
			this->currentHomebrew = this->currentHomebrew + 1;
			this->cursorSound->play();
		}
	}
	else if (key & KEY_UP)
	{
		if (this->currentHomebrew > 0)
		{
			this->currentHomebrew = this->currentHomebrew - 1;
			this->cursorSound->play();
		}
	}

	this->cursor->setPosition(this->currentHomebrew);
}