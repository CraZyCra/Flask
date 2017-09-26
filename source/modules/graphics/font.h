#pragma once

class Font
{
	public:
		const char * DefaultInit();
		const char * Init(const char * path);
		Font(const char * path);
		Font();

		int GetWidth(char glyph);
		int GetWidth(const char * text);

		int GetHeight();

		Glyph * GetGlyph(char glyph);
		Image * GetSheet();

		void AddChars();
		void Collect();

	private:
		File * configFile;
		Image * bitmap;
		nlohmann::json configJson;
		int chars;
		Glyph ** glyphs;
};