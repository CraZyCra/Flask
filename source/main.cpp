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
bool hasError = false;
bool forceQuit = false;
bool audioEnabled = false;

bool consoleEnabled = false;

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

void displayError(const char * error)
{	
	hasError = true;

	consoleInit(GFX_BOTTOM, NULL);

	printf("\n\x1b[31mError: %s\x1b[0m\nPress 'Start' to quit.\n", error);
}

int main()
{
	srand(osGetTime());

	cfguInit();

	ptmuInit();

	if (consoleEnabled) 
		consoleInit(GFX_BOTTOM, NULL);

	Result enableROMFS = romfsInit();

	romfsEnabled = (enableROMFS) ? false : true;

	audioEnabled = !ndspInit();

	if (romfsEnabled) 
		chdir("romfs:/");

	//if (!audioEnabled) 
	//	displayError("DSP Failed to initialize. Please dump your DSP Firm!");

	httpcInit(0);

	mkdir("sdmc:/flask", 0777);

	deltaStep();

	//consoleInit(GFX_BOTTOM, NULL);

	Flask().Run();

	while (hasError)
	{
		hidScanInput();

		u32 kTempDown = hidKeysDown();

		if (kTempDown & KEY_START) 
			break;
	}
	
	cfguExit();

	ptmuExit();

	httpcExit();

	if (romfsEnabled) romfsExit();

	if (audioEnabled) ndspExit();

	return 0;
}