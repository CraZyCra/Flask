#pragma once

class Action
{
	public:
		Action(int id, float x, float y);
		void render();
		void touchPressed(int x, int y);

	private:
		int id;
		
		float x;
		float y;
		float width;
		float height;
};