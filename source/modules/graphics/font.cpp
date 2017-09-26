#include "shared.h"

#include "image.h"
#include "file.h"
#include "quad.h"
#include "glyph.h"
#include "font.h"

using json = nlohmann::json;

Font::Font() {}

Font::Font(const char * path)
{
	if (path != nullptr)
		this->Init(path);
}

const char * Font::Init(const char * path)
{
	std::string fontPath(path);
	std::string configPath(fontPath); 
	configPath.append(".json");
	
	std::string bitmapPath(fontPath); 
	bitmapPath.append(".png");

	this->configFile = new File();

	this->bitmap = new Image();

	this->configFile->InitPath(configPath.c_str());
	this->configFile->Open("r");
	
	std::string data(this->configFile->Read());

	this->configJson = json::parse(data);
	this->configFile->Close();

	this->bitmap->Init(bitmapPath.c_str(), false);

	this->chars = this->configJson["chars"].size();
	
	this->AddChars();
	
	return nullptr;
}

void Font::AddChars()
{
	this->glyphs = new Glyph*[this->chars];
	int i = 0;

	for (auto it = this->configJson["chars"].begin(); it != this->configJson["chars"].end(); it++)
	{
		if (it.value().is_object())
		{
			this->glyphs[i] = new Glyph(it.value());
			i++;
		}
	}
}

Glyph * Font::GetGlyph(char glyph)
{	
	Glyph * ret = nullptr;
	for (int i = 0; i < this->chars; i++)
	{
		if ((int)glyph == this->glyphs[i]->GetChar())
		{
			ret = this->glyphs[i];
			break;
		}
	}

	return ret;
}

Image * Font::GetSheet()
{
	return this->bitmap;
}

int Font::GetWidth(const char * text)
{
	int width = 0;
	
	for (int i = 0; i < strlen(text); i++)
		width += this->GetWidth(text[i]);

	return width;
}

int Font::GetWidth(char glyph)
{
	Glyph * charGlyph = this->GetGlyph(glyph);
	int width = 0;

	if (charGlyph != nullptr)
		width += charGlyph->GetXAdvance();

	return width;
}

int Font::GetHeight()
{
	return this->configJson["info"]["size"];
}

void Font::Collect()
{
	if (this->bitmap != nullptr)
		delete this->bitmap;

	if (this->configFile != nullptr)
		delete this->configFile;

	if (this->glyphs)
	{
		for (int i = 0; i < this->chars; i++)
			delete[] this->glyphs[i];
		
		delete[] this->glyphs;
	}
}