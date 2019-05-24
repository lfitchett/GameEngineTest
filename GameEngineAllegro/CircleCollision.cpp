#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle* c1, Circle* c2)
{
	double dx = c1->GetCenter().x - c2->GetCenter().x;
	double dy = c1->GetCenter().y - c2->GetCenter().y;
	double centerDistSquared = dx * dx + dy * dy;

	double radiusSum = c1->Radius + c2->Radius;
	double radiusSumSquared = radiusSum * radiusSum;

	if (radiusSumSquared >= centerDistSquared) {
		double overlap = radiusSum - sqrt(centerDistSquared);
		return new CollisionInformation{ 
			Point(c2->GetCenter()), 
			Vector(c1->GetCenter(), c2->GetCenter()),
			overlap,
			true
		};
	}

	return false;
}