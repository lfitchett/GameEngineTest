#include "pch.h"

#include <vector>

#define HitboxId uint64_t

struct CircleHitbox
{
	HitboxId parentId;
	double x;
	double y;
	double radius;
	std::function<void(HitboxId)> ifHit;
};

class CollisionManager
{
private:
	std::vector<CircleHitbox*> circles;

	double distanceSquared(CircleHitbox* c1, CircleHitbox* c2)
	{
		return c1->x * c1->x * c2->x * c2->x + c1->y * c1->y * c2->y * c2->y;
	}

public:
	void CheckCollisions()
	{
		for (size_t i = 0; i < circles.size(); i++) {
			for (size_t j = i+1; j < circles.size(); j++) {
				CircleHitbox* c1 = circles[i];
				CircleHitbox* c2 = circles[j];

				double maxDistance = c1->radius + c2->radius;
				if (distanceSquared(c1, c2) <= maxDistance * maxDistance) {
					/* Collision */
					c1->ifHit(c2->parentId);
					c2->ifHit(c1->parentId);
				}
			}
		}
	}

};