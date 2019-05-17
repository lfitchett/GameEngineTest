#include "pch.h"

#include <unordered_map> 

class FontManager {
private:
	std::unordered_map<std::string, ALLEGRO_FONT*> fonts;

public:
	FontManager()
	{
		al_init_font_addon();
	}

	ALLEGRO_FONT* GetFont(std::string fileName)
	{
		auto foundFont = this->fonts.find(fileName);
		if (foundFont != this->fonts.end()) {
			return (*foundFont).second;
		}

		/*ALLEGRO_FONT* newFont = new sf::Font;
		if (!newFont->loadFromFile(fileName))
		{
			printf("Could not find font: %s\n", fileName.c_str());
		}
		this->fonts[fileName] = newFont;
		return *newFont;*/
	}

	ALLEGRO_FONT* GetFont()
	{
		auto foundFont = this->fonts.find("");
		if (foundFont != this->fonts.end()) {
			return (*foundFont).second;
		}

		ALLEGRO_FONT* newFont = al_create_builtin_font();
		this->fonts[""] = newFont;

		return newFont;
	}
};