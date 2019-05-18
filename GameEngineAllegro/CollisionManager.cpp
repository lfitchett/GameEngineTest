#pragma once

#include "pch.h"

#include <vector>
#include "Hitbox.cpp"
#include "Circle.cpp"
#include "Polygon.cpp"

class CollisionManager
{
private:
	std::vector<Hitbox*> hitboxes;

public:
	void AddHitbox(Hitbox* h) 
	{
		hitboxes.push_back(h);
	}

	bool FindCollision(Hitbox* h1)
	{
		for (Hitbox* h2 : hitboxes) {
			if (h2 == h1)
				continue;

			if (isColliding(h1, h2)) {
				return true;
			}
		}

		return false;
	}

private:
	bool isColliding(Hitbox* h1, Hitbox* h2)
	{
		for (size_t i = 0; i < h1->GetSize(); i++) {
			Shape* s1 = h1->GetShapes()[i];
			for (size_t j = 0; j < h2->GetSize(); j++) {
				Shape* s2 = h2->GetShapes()[j];

				if (isColliding(s1, s2)) {
					return true;
				}
			}
		}

		return false;
	}

	bool isColliding(Shape* s1, Shape* s2)
	{
		if (Circle* c1 = dynamic_cast<Circle*>(s1)) {
			if (Circle* c2 = dynamic_cast<Circle*>(s2)) {
				return isColliding(c1, c2);
			}

			if (Polygon* p2 = dynamic_cast<Polygon*>(s2)) {
				return isColliding(c1, p2);
			}
		}
		if (Polygon* p1 = dynamic_cast<Polygon*>(s1)) {
			if (Circle* c2 = dynamic_cast<Circle*>(s2)) {
				return isColliding(c2, p1);
			}

			if (Polygon* p2 = dynamic_cast<Polygon*>(s2)) {
				return isColliding(p1, p2);
			}
		}

		return false;
	}

	bool isColliding(Circle* c1, Circle* c2)
	{
		double dx = c1->Center.x - c2->Center.x;
		double dy = c1->Center.y - c2->Center.y;
		double centerDistSquared = dx * dx + dy * dy;

		double sr = c1->Radius + c2->Radius;
		double radiusSumSquared = sr*sr;

		return radiusSumSquared >= centerDistSquared;
	}

	bool isColliding(Circle* c1, Polygon* p2)
	{
		return false;
	}

	bool isColliding(Polygon* p1, Polygon* p2)
	{
		return false;
	}
};