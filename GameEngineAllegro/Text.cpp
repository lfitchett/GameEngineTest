#include "pch.h"

#include "EntityWithData.cpp"

class Text : public EntityWithData
{
public:
	sf::Text* text;

	Text(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		this->text = new sf::Text;
		this->text->setFont(this->sharedData.fontManager.GetFont("C:/Users/lfitc/source/repos/GameEngine/GameEngine/arial.ttf"));

		this->text->setString("Hello world");
		this->text->setCharacterSize(240); // in pixels, not points!
		this->text->setFillColor(sf::Color::Red);
		this->text->setStyle(sf::Text::Bold | sf::Text::Underlined);
	}

	~Text() {
		delete this->text;
		printf("Cleanup Text\n");
	}

protected:
	void Tick()
	{
		this->sharedData.window->draw(*this->text);
	}
};
