#pragma once

class Flask : public Scene
{
	public:
		void update(float dt) override;
		void render() override;
		void keyPressed(u32 key) override;
		void touchPressed(int x, int y) override;
		Flask();

	private:
		std::vector<Bubble> * bubbles;

		sf2d_texture * bubbleTexture;
		
		Image * wifiSignal;
		Image * batteryDisplay;
		Image * listDisplay;
		Image * updateDisplay;
		Image * searchDisplay;
		
		OggVorbis * cursorSound;
		
		float bubbleTimer;
		std::vector<Quad> * batteryQuads;

		char * state;

		Cursor * cursor;

		int currentHomebrew;

		float smoothScroll;
};