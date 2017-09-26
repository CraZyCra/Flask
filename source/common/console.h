#pragma once

class Console 
{
	public:
		Console();
		bool IsEnabled();
		void Enable(gfxScreen_t screen);

		int ThrowError(const char * message);
		gfxScreen_t GetScreen();
		const char * GetError();

	private:
		const char * errorMessage;
		gfxScreen_t screen;
		bool enabled;
};