#pragma once

#include "Hitbox.cpp"
#include "Circle.cpp"
#include "Polygon.cpp"
#include "CollisionInformation.cpp"

#define CollisionResult std::unique_ptr<CollisionInformation>

class CollisionManager
{
private:
	std::vector<Hitbox*> hitboxes;

public:
	void AddHitbox(Hitbox* h);
	void RemoveHitbox(Hitbox* h);
	CollisionResult FindCollision(Hitbox* h1);
};