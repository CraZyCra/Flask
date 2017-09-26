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

#include "objects/flask.h"
#include "modules/graphics/graphics.h"
#include "modules/audio/source.h"
#include "modules/system/core.h"

bool romfsEnabled = false;
bool audioEnabled = false;
bool QUIT_APP = false;

Console * console;
std::vector<Source *> streams;

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

	console = new Console();
	//console->Enable(GFX_BOTTOM);

	Flask * mainApp = new Flask();

	Source * intro = new Source("audio/loop.ogg", "static");
	intro->SetLooping(true);
	intro->Play();

	while (aptMainLoop())
	{
		if (QUIT_APP)
			break;
	
		scanInput(mainApp);

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