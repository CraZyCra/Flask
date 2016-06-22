#pragma once

class Cursor
{
	public:
		Cursor();
		void setPosition(int selection);
		void update(float dt);
		void render(float translateValue);

	private:
		float x;
		float y;
		float width;
		float height;

		float timer;
		float sineValue;
};