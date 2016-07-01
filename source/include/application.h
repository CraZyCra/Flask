#pragma once

class Application
{
	public:
		Application(float x, float y);
		void setIcon(Image * icon);
		void render(float translateValue);
		void setDownloadURL(const char * url);
		void setName(const char * name);
		void setAuthor(const char * author);
		void setDescription(const char * description);

	private:
		float x;
		float y;
		
		char * name;
		char * author;
		char * description;
		char * downloadURL;

		Image * icon;
		Image * downloadIcon;

		size_t size;
};