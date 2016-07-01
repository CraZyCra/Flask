#include "shared.h"

Intro::Intro()
{
	sf2d_texture * bannerTexture = sfil_load_PNG_file("graphics/banner.png", SF2D_PLACE_RAM);
	this->banner = new Image(bannerTexture);

	OggVorbis jingle("audio/intro.ogg");

	sf2d_texture * loadingRing = sfil_load_PNG_file("graphics/loading.png", SF2D_PLACE_RAM);
	this->loader = new Image(loadingRing);

	this->loadRotation = 0;

	s32 priority = 0;
	svcGetThreadPriority(&priority, CUR_THREAD_HANDLE);
	Thread songThread = threadCreate(loadBackgroundSong, NULL, 8192, priority - 1, -2, true);

	this->bubbleTexture = sfil_load_PNG_file("graphics/bubble.png", SF2D_PLACE_RAM);
	this->bubbleTimer = rand() % 2 + 1;

	jingle.play();

	cacheData();
}

void Intro::update(float dt)
{
	this->loadRotation += 4 * dt;

	for (int i = 0; i < (*bubbles).size(); i++)
	{
		(*bubbles)[i].update(dt);
		if ((*bubbles)[i].shouldRemove() == true)
		{
			(*bubbles)[i].resetBubble();
		}
	}

	if ((*bubbles).size() < 30)
	{
		if (this->bubbleTimer > 0)
		{
			this->bubbleTimer -= dt;
		}
		else
		{	
			Bubble temp(this->bubbleTexture);
			bubbles->push_back(temp);
			this->bubbleTimer = rand() % 2 + 1;
		}
	}
}

void Intro::render()
{
	for (int i = 0; i < (*bubbles).size(); i++)
	{
		if ((*bubbles)[i].getZOrder() == 0)
		{
			(*bubbles)[i].render();
		}
	}

	setScreen(GFX_TOP);

	this->banner->render(200 - this->banner->getWidth() / 2, 120 - this->banner->getHeight()/  2);

	authorFont->print(flaskVersion, 400 - authorFont->getWidth(flaskVersion) - 2, 240 - authorFont->getHeight() - 2);

	setScreen(GFX_BOTTOM);

	this->loader->render(160 - this->loader->getWidth() / 2, 120 - this->loader->getHeight() / 2, this->loadRotation);

	for (int i = 0; i < (*bubbles).size(); i++)
	{
		if ((*bubbles)[i].getZOrder() == 1)
		{
			(*bubbles)[i].render();
		}
	}
}

void Intro::keyPressed(u32 key)
{

}

void Intro::touchPressed(int x, int y)
{

}