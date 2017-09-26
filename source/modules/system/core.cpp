#include "core.h"

char BUTTONS[32][32] = {
	"a", "b", "select", "start",
	"right", "left", "up", "down",
	"rbutton", "lbutton", "x", "y",
	"", "", "lzbutton", "rzbutton",
	"", "", "", "",
	"touch", "", "", "",
	"cstickright", "cstickleft", "cstickup", "cstickdown",
	"cpadright", "cpadleft", "cpadup", "cpaddown"
};

int prevTime = 0;
int currTime = 0;
float dt;

touchPosition touch;
int lastTouch[2];

float deltaStep()
{
	prevTime = currTime;

	currTime = osGetTime();

	dt = currTime - prevTime;

	dt = dt * 0.001;

	if (dt < 0) dt = 0; // Fix nasty timer bug

	return dt;
}

void scanInput(Flask * flask)
{
	hidScanInput();
	
	u32 keyDown = hidKeysDown();
	u32 keyUp = hidKeysUp();
	
	for (int i = 0; i < 32; i++)
	{
		if (keyDown & BIT(i))
		{
			if (strcmp(BUTTONS[i], "touch") != 0)
				flask->KeyPressed(std::string(BUTTONS[i]));
			else
			{
				hidTouchRead(&touch);
				
				flask->Touch(touch.px, touch.py);

				lastTouch[0] = touch.px;
				lastTouch[1] = touch.py;
			}
		}
		else if (keyUp & BIT(i))
		{
			if (strcmp(BUTTONS[i], "touch") != 0)
				flask->KeyReleased(std::string(BUTTONS[i]));
			else
				flask->TouchReleased(lastTouch[0], lastTouch[1]);
		}
	}
}