#pragma once

class Bubble
{
	public:
		Bubble(sf2d_texture * texture);
		void render();
		void update(float dt);
		void resetBubble();
		bool shouldRemove();

	private:
		sf2d_texture * graphic;
		int x;
		int y;
		int width;
		int height;
		const char * currentScreen;
		bool remove;
};