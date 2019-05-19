#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle* c1, Circle* c2)
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