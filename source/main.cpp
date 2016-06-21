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
bool loadSong = false;

bool consoleEnabled = true;

Thread songThread;
s32 threadPriority = 0;

int prevTime = 0;
int currTime = 0;
float dt;

Font * nameFont;
Font * descriptionFont;
Font * authorFont;

std::vector<Application> * applications;
std::vector<Quad> * icons;

float deltaStep()
{
	prevTime = currTime;

	currTime = osGetTime();

	dt = currTime - prevTime;

	dt = dt * 0.001;

	if (dt < 0) dt = 0; // Fix nasty timer bug

	return dt;
}

void displayError(const char * error)
{
	FILE * file = fopen("sdmc:/Flask.txt", "w");

	fwrite(error, strlen(error), 1, file);

	fflush(file);

	fclose(file);
	
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

	deltaStep();

	svcGetThreadPriority(&threadPriority, CUR_THREAD_HANDLE);

	songThread = threadCreate(loadBackgroundSong, NULL, 1024, threadPriority - 1, -2, true);

	nameFont = new Font("fonts/LiberationSans-Bold.ttf", 16);
	descriptionFont = new Font("fonts/LiberationSans-Regular.ttf", 16);
	//authorFont = new Font("fonts/LiberationSans-Italic.ttf", 16);

	applications = new std::vector<Application>();
	icons = new std::vector<Quad>();

	cacheData();

	Flask * flask = new Flask();

	while (aptMainLoop())
	{
		if (!hasError)
		{
			flask->keyPressed(hidKeysDown());

			flask->update(deltaStep()); //wee

			//Start top screen
			sf2d_start_frame(GFX_TOP, GFX_LEFT);

			flask->render();
			
			sf2d_end_frame();
		
			//Start bottom screen
			if (!consoleEnabled)
			{
				sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

				flask->render();

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

	return 0;
}