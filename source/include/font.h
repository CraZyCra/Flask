#pragma once

class Font
{
	public:
		Font(const char * filename, int size);
		Font(const char * filename);
		~Font();
		void setSize(int size);
		int getWidth(const char * text);
		int getHeight();
		void print(const char * text, float x, float y);
		void print(const char * text, float x, float y, int size);
		
	private:
		int size;
		sftd_font * font;
};