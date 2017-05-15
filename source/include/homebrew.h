#pragma once

class Homebrew
{
	public:
		Homebrew(std::shared_ptr<starlight::ui::Form>, int i, string name, json properties);
		
	private:
		string name;
		string category;
		string url;

		string author;
		string version;
};