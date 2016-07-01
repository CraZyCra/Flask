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

bool romfsEnabled = false;
bool channelList[24];
bool hasError = false;
bool forceQuit = false;
bool audioEnabled = false;

bool consoleEnabled = false;

int prevTime = 0;
int currTime = 0;
float dt;

Font * nameFont;
Font * descriptionFont;
Font * authorFont;

std::vector<Application> * applications;
std::vector<Quad> * icons;
std::vector<Bubble> * bubbles;

Intro * flaskIntro;
Flask * flaskMain;

int currentScene;
char * flaskVersion = "v0.1";

float deltaStep()
{
	prevTime = currTime;

	currTime = osGetTime();

	dt = currTime - prevTime;

	dt = dt * 0.001;

	if (dt < 0) dt = 0; // Fix nasty timer bug

	return dt;
}

Scene * getScene()
{
	switch(currentScene)
	{
		case SC_INTRO:
			return flaskIntro;
		case SC_FLASK:
			return flaskMain;
		default:
			displayError("Invalid scene.");
			break;
	}
}

void setScene(int scene)
{
	currentScene = scene;
}

void displayError(const char * error)
{	
	sf2d_set_clear_color(RGBA8(0, 0, 0, 0xFF));

	hasError = true;

	consoleInit(GFX_TOP, NULL);

	printf("\n\x1b[31mError: %s\x1b[0m\nPress 'Start' to quit.\n", error);
}

int main()
{
	srand(osGetTime());

	sf2d_init(); // 2D Drawing lib.

	sftd_init(); // Text Drawing lib.

	cfguInit();

	ptmuInit();

	if (consoleEnabled) consoleInit(GFX_BOTTOM, NULL);

	sf2d_set_clear_color(RGBA8(61, 142, 185, 0xFF)); // Reset background color.

	Result enableROMFS = romfsInit();

	romfsEnabled = (enableROMFS) ? false : true;

	audioEnabled = !ndspInit();

	if (romfsEnabled) chdir("romfs:/");

	if (!audioEnabled) displayError("DSP Failed to initialize. Please dump your DSP Firm!");

	httpcInit(0);

	mkdir("sdmc:/flask", 0777);

	deltaStep();

	nameFont = new Font("fonts/LiberationSans-Bold.ttf", 16);
	descriptionFont = new Font("fonts/LiberationSans-Regular.ttf", 16);
	authorFont = new Font("fonts/LiberationSans-Italic.ttf", 16);

	applications = new std::vector<Application>();
	icons = new std::vector<Quad>();
	bubbles = new std::vector<Bubble>();

	flaskIntro = new Intro();
	flaskMain = new Flask();

	setScene(SC_INTRO);

	while (aptMainLoop())
	{
		if (!hasError)
		{
			hidScanInput();
			
			getScene()->keyPressed(hidKeysDown());

			touchPosition mouse;

			hidTouchRead(&mouse);

			getScene()->touchPressed(mouse.px, mouse.py);

			getScene()->update(deltaStep()); //wee

			//Start top screen
			sf2d_start_frame(GFX_TOP, GFX_LEFT);

			getScene()->render();
			
			sf2d_end_frame();
		
			//Start bottom screen
			if (!consoleEnabled)
			{
				sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

				getScene()->render();

				sf2d_end_frame();
			}

			sf2d_swapbuffers();
		}
		else
		{
			hidScanInput();

			u32 kTempDown = hidKeysDown();

			if (kTempDown & KEY_START) 
			{
				break;
			}
		}
	}

	sftd_fini();

	sf2d_fini();

	cfguExit();

	ptmuExit();

	httpcExit();

	if (romfsEnabled) romfsExit();

	if (audioEnabled) ndspExit();

	delete flaskIntro;

	delete flaskMain;

	return 0;
}