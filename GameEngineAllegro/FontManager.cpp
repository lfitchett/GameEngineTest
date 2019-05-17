#include "pch.h"

#include <unordered_map> 

class FontManager {
private:
	std::unordered_map<std::string, sf::Font*> fonts;

public:
	sf::Font& GetFont(std::string fileName) {
		auto foundFont = this->fonts.find(fileName);
		if (foundFont != this->fonts.end()) {
			return *(*foundFont).second;
		}

		sf::Font* newFont = new sf::Font;
		if (!newFont->loadFromFile(fileName))
		{
			printf("Could not find font: %s\n", fileName.c_str());
		}
		this->fonts[fileName] = newFont;
		return *newFont;
	}
};