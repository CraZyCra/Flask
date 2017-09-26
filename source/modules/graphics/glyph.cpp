#include "shared.h"
#include "quad.h"
#include "glyph.h"

using json = nlohmann::json;

Glyph::Glyph(json config)
{
	this->glyph = config["id"];

	int x = config["x"];
	int y = config["y"];
	int charWidth = config["width"];
	int charHeight = config["height"];

	this->quad = new Quad();
	this->quad->Init(x, y, charWidth, charHeight);

	this->xadvance = config["xadvance"];
	this->yoffset = config["yoffset"];
	this->xoffset = config["xoffset"];
	this->width = charWidth;
}

Quad * Glyph::GetQuad()
{
	return this->quad;
}

int Glyph::GetXAdvance()
{
	return this->xadvance;
}

int Glyph::GetYOffset()
{
	return this->yoffset;
}

int Glyph::GetXOffset()
{
	return this->xoffset;
}

int Glyph::GetWidth()
{
	return this->width;
}

int Glyph::GetChar()
{
	return this->glyph;
}