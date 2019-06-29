#include "pch.h"

#include <allegro5/allegro_ttf.h>

class FontManager {
private:
	std::unordered_map<std::string, ALLEGRO_FONT*> fonts;

public:
	FontManager()
	{
		al_init_font_addon();
		al_init_ttf_addon();
	}

	ALLEGRO_FONT* GetFont(std::string fileName, int size = 12)
	{
		auto foundFont = this->fonts.find(fileName);
		if (foundFont != this->fonts.end()) {
			return (*foundFont).second;
		}

		ALLEGRO_FONT* newFont = al_load_ttf_font(fileName.c_str(), size, 0);
		if (!newFont)
		{
			printf("Could not find font: %s\n", fileName.c_str());
		}
		this->fonts[fileName] = newFont;
		return newFont;
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