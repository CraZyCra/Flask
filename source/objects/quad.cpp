#include <shared.h>

Quad::Quad(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int Quad::getX()
{
	return this->x;
}

int Quad::getY()
{
	return this->y;
}

int Quad::getWidth()
{
	return this->width;
}

int Quad::getHeight()
{
	return this->height;
}