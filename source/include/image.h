#pragma once

class Image
{
	public:
		Image(sf2d_texture * texture);
		void render(float x, float y);
		void render(Quad quad, float x, float y);
		int getWidth();
		int getHeight();
		
	private:
		sf2d_texture * texture;
		int width;
		int height;
};