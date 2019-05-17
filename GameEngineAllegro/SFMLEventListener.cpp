#include "pch.h"

#include "EntityWithData.cpp"

class SFMLEventListener : public EntityWithData {
	using EntityWithData::EntityWithData;


protected:
	void Tick() {
		printf("Checking for events\n");
		sf::Event event;
		while (this->sharedData.window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				printf("Window Closed\n");
				this->sharedData.window->close();
				this->mainLoop.Stop();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					this->sharedData.mouseClickLocation.x = event.mouseButton.x;
					this->sharedData.mouseClickLocation.y = event.mouseButton.y;
				}
				break;

			case sf::Event::MouseMoved:
				this->sharedData.mouseLocation.x = event.mouseMove.x;
				this->sharedData.mouseLocation.y = event.mouseMove.y;
				break;

			default:
				break;
			}
		}
	}
};

