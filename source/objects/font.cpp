#include <shared.h>

Font::Font(const char * filename, int size)
{
	this->font = sftd_load_font_file(filename);
	this->size = size;
}

Font::Font(const char * filename)
{
	this->font = sftd_load_font_file(filename);
	this->size = 16;
}

int Font::getWidth(const char * text)
{
	return sftd_get_text_width(this->font, this->size, text);
}

int Font::getHeight()
{
	return this->size;
}

void Font::setSize(int size)
{
	this->size = size;
}

void Font::print(const char * text, float x, float y)
{
	if (sf2d_get_current_screen() == getCurrentScreen()) 
	{
		sftd_draw_text(this->font, x, y, getCurrentColor(), this->size, text);
	}
}

void Font::print(const char * text, float x, float y, int size)
{
	if (sf2d_get_current_screen() == getCurrentScreen()) 
	{
		sftd_draw_text(this->font, x, y, getCurrentColor(), size, text);
	}
}