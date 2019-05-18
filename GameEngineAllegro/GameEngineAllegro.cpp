// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "CollisionManager.cpp";

int main()
{
	Circle* c1 = new Circle(5, 5, 10);
	Hitbox* h1 = new SingleHitbox(c1);

	Circle* c2 = new Circle(7, 7, 10);
	Hitbox* h2 = new SingleHitbox(c2);

	CollisionManager manager;
	manager.AddHitbox(h1);
	manager.AddHitbox(h2);

	bool test = manager.FindCollision(h1);


	return 0;
}
