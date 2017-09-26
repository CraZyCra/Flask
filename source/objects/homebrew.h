#pragma once

#include "shared.h"

enum HOMEBREW_CATERGORY {
	UTILITY = 0,
	THEME = 1,
	GAME = 2
};

class Homebrew
{
	public:
		Homebrew();
		int GetID();
		void SetHighlight();

	private:
		std::string name;
		HOMEBREW_CATERGORY category;
		std::string url;

		std::string author;
		std::string version;

		int id;
};