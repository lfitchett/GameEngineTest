#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle& c1, Circle& c2)
{
	double dx = c1.center.x - c2.center.x;
	double dy = c1.center.y - c2.center.y;
	double centerDistSquared = dx * dx + dy * dy;

	double radiusSum = c1.radius + c2.radius;
	double radiusSumSquared = radiusSum * radiusSum;

	if (radiusSumSquared >= centerDistSquared) {
		double overlap = radiusSum - sqrt(centerDistSquared);
		return new CollisionInformation{
			Vector(c1.center, c2.center),
			overlap
		};
	}

	return false;
}