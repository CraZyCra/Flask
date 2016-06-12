#pragma once

class Quad
{
	public:
		Quad(int x, int y, int width, int height);
		void render();
		int getX();
		int getY();
		int getWidth();
		int getHeight();

	private:
		int x;
		int y;
		int width;
		int height;
};