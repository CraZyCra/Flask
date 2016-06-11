#pragma once

class Flask
{
	public:
		void update(float dt);
		void render();
		Flask();
		~Flask();

	private:
		std::vector<Bubble> bubbles;
		sf2d_texture * bubbleGraphic;
};