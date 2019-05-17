#include "pch.h"

#include "EntityWithData.cpp"

class Circle : public EntityWithData
{
public:
	Circle(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		this->shape = new sf::CircleShape(50.f);
		this->shape->setFillColor(sf::Color::Green);

		this->currLocation = this->sharedData.mouseClickLocation;
	}

	~Circle() {
		delete this->shape;
		printf("Cleanup Circle\n");
	}

private:
	sf::CircleShape* shape;
	Location currLocation;

protected:
	void Tick()
	{
		this->currLocation.x = this->sharedData.mouseLocation.x - (50);
		this->currLocation.y = this->sharedData.mouseLocation.y - (50);

		this->shape->setPosition(this->currLocation.x, this->currLocation.y);
		this->currLocation.print();
		this->sharedData.window->draw(*this->shape);
	}
};
