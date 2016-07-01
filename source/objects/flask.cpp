#include "shared.h"

Flask::Flask()
{
	sf2d_texture * wifiTexture = sfil_load_PNG_file("graphics/wifi.png", SF2D_PLACE_RAM);
	sf2d_texture * batteryTexture = sfil_load_PNG_file("graphics/battery.png", SF2D_PLACE_RAM);
	sf2d_texture * listTexture = sfil_load_PNG_file("graphics/list.png", SF2D_PLACE_RAM);
	sf2d_texture * updateTexture = sfil_load_PNG_file("graphics/updates.png", SF2D_PLACE_RAM);
	sf2d_texture * searchTexture = sfil_load_PNG_file("graphics/search.png", SF2D_PLACE_RAM);

	this->batteryQuads = new std::vector<Quad>();

	for (int i = 1; i < 6; i++)
	{
		Quad temp((i - 1) * 16, 0, 16, 9);
		this->batteryQuads->push_back(temp);
	}

	this->bubbleTimer = rand() % 2 + 1;

	this->wifiSignal = new Image(wifiTexture);
	this->batteryDisplay = new Image(batteryTexture);
	
	this->listDisplay = new Image(listTexture);
	this->updateDisplay = new Image(updateTexture);
	this->searchDisplay = new Image(searchTexture);

	this->cursorSound = new OggVorbis("audio/cursor.ogg");
	this->cursorSound->setVolume(0.35);

	this->cursor = new Cursor();

	this->currentHomebrew = 0;
	this->smoothScroll = 0;

	this->state = "list";
}

void Flask::update(float dt)
{
	for (int i = 0; i < bubbles->size(); i++)
	{
		(*bubbles)[i].update(dt);
		if ((*bubbles)[i].shouldRemove() == true)
		{
			(*bubbles)[i].resetBubble();
		}
	}

	this->cursor->update(dt);

	if (this->currentHomebrew < applications->size() - 2)
	{
		this->smoothScroll = this->smoothScroll + ((this->currentHomebrew * 64) - this->smoothScroll) * SCROLLRATE * dt;
	}
	else
	{
		this->smoothScroll = this->smoothScroll + (((applications->size() - 3) * 64) - this->smoothScroll) * SCROLLRATE * dt;
	}
}

void Flask::render()
{	
	for (int i = 0; i < (*bubbles).size(); i++)
	{
		if ((*bubbles)[i].getZOrder() == 0)
		{
			(*bubbles)[i].render();
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

	this->cursor->render(this->smoothScroll);

	setColor(255, 255, 255);

	for (int i = 0; i < applications->size(); i++)
	{
		setScissor(24, 24, 272, 192);
		
		(*applications)[i].render(this->smoothScroll);

		setScissor(NULL, NULL, NULL, NULL);
	}

	setColor(255, 255, 255);
	this->listDisplay->render(320 * 1/4 - 8, 220);

	setColor(117, 112, 107);
	this->updateDisplay->render(320 * 1/2 - 8, 220);

	setColor(117, 112, 107);
	this->searchDisplay->render(320 * 3/4 - 8, 220);

	setColor(255, 255, 255);

	for (int i = 0; i < (*bubbles).size(); i++)
	{
		if ((*bubbles)[i].getZOrder() == 1)
		{
			(*bubbles)[i].render();
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

void Flask::touchPressed(int x, int y)
{
	
}