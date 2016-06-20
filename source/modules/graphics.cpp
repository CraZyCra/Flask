#include <shared.h>

int currentR = 0xFF;
int currentG = 0xFF;
int currentB = 0xFF;
int currentA = 0xFF;

int currentScreen = GFX_BOTTOM;

u32 getCurrentColor() 
{
	return RGBA8(currentR, currentG, currentB, currentA);
}

void setColor(int r, int g, int b)
{
	currentR = r;
	currentG = g;
	currentB = b;
	currentA = currentA;
}

void setColor(int r, int g, int b, int a)
{
	currentR = r;
	currentG = g;
	currentB = b;
	currentA = a;
}

void setScreen(int screen)
{
	currentScreen = screen;
}

int getCurrentScreen()
{
	return currentScreen;
}

void screenShot() //for showing stuff being done
{
	FILE * topScreen = fopen("sdmc:/framebuffer_top.rgb", "w+");

	fwrite(gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL), 288000, 1, topScreen);

	fclose(topScreen);

	FILE * bottomScreen = fopen("sdmc:/framebuffer_bottom.rgb", "w+");;

	fwrite(gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL), 230400, 1, bottomScreen);

	fclose(bottomScreen);
}