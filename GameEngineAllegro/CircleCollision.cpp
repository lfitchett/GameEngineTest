#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle* circ1, Circle* circ2)
{
	Point c1 = circ1->GetCenter();
	Point c2 = circ2->GetCenter();
	double dx = c1.x - c2.x;
	double dy = c1.y - c2.y;
	double centerDistSquared = dx * dx + dy * dy;

	double radiusSum = circ1->Radius + circ2->Radius;
	double radiusSumSquared = radiusSum * radiusSum;

	if (radiusSumSquared >= centerDistSquared) {
		double overlap = radiusSum - sqrt(centerDistSquared);
		return new CollisionInformation{ 
			Vector(c1, c2),
			overlap,
			true
		};
	}

	return false;
}