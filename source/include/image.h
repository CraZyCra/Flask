#pragma once

class Image
{
	public:
		Image(sf2d_texture * texture);
		~Image();
		void render(float x, float y);
		void render(Quad quad, float x, float y);
		void render(float x, float y, float rotation);
		int getWidth();
		int getHeight();
		
	private:
		sf2d_texture * texture;
		int width;
		int height;
};
