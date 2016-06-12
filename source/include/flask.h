#pragma once

class Flask
{
	public:
		void update(float dt);
		void render();
		Flask();
		~Flask();

	private:
		std::vector<Bubble> * bubbles;

		sf2d_texture * bubbleTexture;
		sf2d_texture * wifiTexture;
		sf2d_texture * batteryTexture;
		sf2d_texture * listTexture;
		sf2d_texture * updateTexture;
		sf2d_texture * searchTexture;

		Image * wifiSignal;
		Image * batteryDisplay;
		Image * listDisplay;
		Image * updateDisplay;
		Image * searchDisplay;
		
		float bubbleTimer;
		std::vector<Quad> * batteryQuads;
		Font * interfacFont;
};