#pragma once

#include "Hitbox.cpp"
#include "Circle.cpp"
#include "Polygon.cpp"
#include "CollisionInformation.cpp"

typedef std::unique_ptr<CollisionInformation> CollisionResult;

class CollisionManager
{
private:
	std::vector<Hitbox*> hitboxes;

public:
	void AddHitbox(Hitbox* h);
	void RemoveHitbox(Hitbox* h);
	CollisionResult FindCollision(Hitbox* h1);

private:
	CollisionInformation* isColliding(Hitbox& h1, Hitbox& h2);
	CollisionInformation* isColliding(Shape* s1, Shape* s2);
	CollisionInformation* isColliding(Circle& c1, Circle& c2);
	CollisionInformation* isColliding(Circle& c1, Polygon& p2);
	CollisionInformation* isColliding(Polygon& p1, Circle& c2);
	CollisionInformation* isColliding(Polygon& p1, Polygon& p2);
};