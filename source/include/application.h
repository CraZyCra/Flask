#pragma once

class Application
{
	public:
		Application(float x, float y, const char * name, const char * author, const char * description);
		void setIcon(Image * icon);
		void render();
		void setDownloadURL(const char * url);

	private:
		float x;
		float y;
		
		const char * name;
		const char * author;
		const char * description;
		const char * downloadURL;

		Image * icon;

		size_t size;
};