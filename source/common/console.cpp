#include "shared.h"
#include "console.h"

Console::Console()
{
	this->enabled = false;
}

void Console::Enable(gfxScreen_t screen)
{
	if (!this->IsEnabled())
		this->enabled = true;

	consoleInit(screen, NULL);
	this->screen = screen;
}

gfxScreen_t Console::GetScreen()
{
	return this->screen;
}

bool Console::IsEnabled()
{
	return this->enabled;
}

const char * Console::GetError()
{
	return this->errorMessage;
}

int Console::ThrowError(const char * errorMessage)
{
	if (errorMessage == nullptr)
		return 0;

	this->errorMessage = errorMessage;
	printf("\e[31;1m%s\e[0m\n", errorMessage);

	return 0;
}