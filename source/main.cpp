/*
	The MIT License (MIT)

	Copyright (c) 2016 Jeremy 'TurtleP' Postelnek - jeremy.postelnek@gmail.com

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "shared.h"
#include "include/flask.h"
#include "wrap_graphics.h"
#include "include/source.h"

bool romfsEnabled = false;
bool hasError = false;
bool forceQuit = false;
bool audioEnabled = false;
std::vector<Source *> streams;
love::Console * console;
bool QUIT_APP = false;

bool consoleEnabled = false;

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

float deltaStep()
{
	prevTime = currTime;

	currTime = osGetTime();

	dt = currTime - prevTime;

	dt = dt * 0.001;

	if (dt < 0) dt = 0; // Fix nasty timer bug

	return dt;
}

int main()
{
	srand(osGetTime());
	
	romfsEnabled = (romfsInit()) ? false : true;

	audioEnabled = !ndspInit();

	ptmuInit();

	if (romfsEnabled) 
		chdir("romfs:/");
	else
	{
		char cwd[256];
		getcwd(cwd, 256);

		strcat(cwd, "assets/");

		chdir(cwd);
	}

	for (int i = 0; i <= 23; i++) 
		channelList[i] = false;

	httpcInit(0);

	deltaStep();

	graphicsInit();

	console = new love::Console();
	console->Enable(GFX_BOTTOM);

	Flask * mainApp = new Flask();

	touchPosition touch;

	Source * intro = new Source("audio/loop.ogg", "static");
	intro->SetLooping(true);
	intro->Play();

	while (aptMainLoop())
	{
		if (QUIT_APP)
			break;

		hidScanInput();

		u32 keyDown = hidKeysDown();

		for (int i = 0; i < 32; i++)
		{
			if (keyDown & BIT(i))
			{	
				if (strcmp(BUTTONS[i], "touch") != 0)
					mainApp->KeyPressed(std::string(BUTTONS[i]));
			}
		}

		if (keyDown & BIT(20))
		{
			hidTouchRead(&touch);
		
			mainApp->Touch(touch.px, touch.py);
		}
	
		mainApp->Update(deltaStep());
		
		graphicsRender(GFX_TOP);

		mainApp->Render();
		
		if (!console->IsEnabled())
		{
			graphicsRender(GFX_BOTTOM);

			mainApp->Render();
		}

		graphicsSwapBuffers();
	}

	httpcExit();

	ptmuExit();

	if (romfsEnabled) romfsExit();

	if (audioEnabled) ndspExit();

	return 0;
}