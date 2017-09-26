#pragma once

class Quad
{
	public:
		const char * Init(int x, int y, int width, int height);
		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();

	private:
		int x;
		int y;
		int width;
		int height;
};