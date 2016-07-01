#pragma once

class Scene 
{
	public:
		virtual ~Scene() = 0;
		virtual void update(float dt) = 0;
		virtual void render() = 0;
		virtual void keyPressed(u32 key) = 0;
		virtual void touchPressed(int x, int y) = 0;
};