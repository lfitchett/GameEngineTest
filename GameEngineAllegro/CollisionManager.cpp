#pragma once

#include "pch.h"

#include <vector>
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
	void AddHitbox(Hitbox* h)
	{
		hitboxes.push_back(h);
	}

	void RemoveHitbox(Hitbox* h)
	{
		for (size_t i = 0; i < hitboxes.size(); i++) {
			if (hitboxes[i] == h) {
				hitboxes.erase(hitboxes.begin() + i);
			}
		}
	}

	CollisionResult FindCollision(Hitbox* h1)
	{
		CollisionInformation* result;
		for (Hitbox* h2 : hitboxes) {
			if (h2 == h1)
				continue;

			if (result = isColliding(h1, h2)) {
				return CollisionResult(result);
			}
		}

		return false;
	}

private:
	CollisionInformation* isColliding(Hitbox* h1, Hitbox* h2)
	{
		CollisionInformation* result;

		for (size_t i = 0; i < h1->GetSize(); i++) {
			Shape* s1 = h1->GetShapes()[i];
			for (size_t j = 0; j < h2->GetSize(); j++) {
				Shape* s2 = h2->GetShapes()[j];

				if (result = isColliding(s1, s2)) {
					return result;
				}
			}
		}

		return false;
	}

	CollisionInformation* isColliding(Shape* s1, Shape* s2)
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
				return isColliding(p1, c2);
			}

			if (Polygon* p2 = dynamic_cast<Polygon*>(s2)) {
				return isColliding(p1, p2);
			}
		}

		return false;
	}

	CollisionInformation* isColliding(Circle* c1, Circle* c2)
	{
		double dx = c1->GetCenter().x - c2->GetCenter().x;
		double dy = c1->GetCenter().y - c2->GetCenter().y;
		double centerDistSquared = dx * dx + dy * dy;

		double sr = c1->Radius + c2->Radius;
		double radiusSumSquared = sr * sr;

		if (radiusSumSquared >= centerDistSquared) {
			CollisionInformation* result = new CollisionInformation();
			result->OtherCenter = &c2->GetCenter();
			return result;
		}

		return false;
	}

	CollisionInformation* isColliding(Circle* c1, Polygon* p2)
	{
		return false;
	}

	CollisionInformation* isColliding(Polygon* p1, Circle* c2)
	{
		return false;
	}

	CollisionInformation* isColliding(Polygon* p1, Polygon* p2)
	{
		return false;
	}
};