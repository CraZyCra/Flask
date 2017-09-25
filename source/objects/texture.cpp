#include "include/texture.h"

Texture::Texture(const char * path)
{
	this->graphic = new Image(path);

	this->width = this->graphic->GetWidth();
	this->height = this->graphic->GetHeight();
}

void Texture::Render(float x, float y)
{
	bindTexture(this->graphic->GetTexture());
	graphicsDraw(this->graphic->GetTexture(), x, y, this->graphic->GetWidth(), this->graphic->GetHeight(), 0, 1, 1);
}

int Texture::GetWidth()
{
	return this->width;
}

int Texture::GetHeight()
{
	return this->height;
}