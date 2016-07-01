#pragma once

class Intro : public Scene
{
	public:
		Intro();
		void render() override;
		void update(float dt) override;
		void keyPressed(u32 key) override;
		void touchPressed(int x, int y) override;

	private:
		Image * banner;
		Image * loader;
		sf2d_texture * bubbleTexture;
		float loadRotation;
		float bubbleTimer;
};