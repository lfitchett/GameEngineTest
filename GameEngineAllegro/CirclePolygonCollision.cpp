#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle* circ, Polygon* poly)
{
	/* Check outside bounds */
	Point c = circ->GetCenter();
	double r = circ->Radius;
	RectangleBound circleBound{ c.x + r, c.y + r, c.x - r, c.y - r };
	if (!circleBound.intersects(poly->GetBounds())) {
		return false;
	}

	size_t n = poly->GetNumPoints();
	Point* pStart = poly->GetPoints();
	Point* pEnd = pStart + n;

	Point* closestPoint;
	double minDistance = DBL_MAX;
	for (Point* p = pStart; p < pEnd; p++) {
		double dx = c.x - p->x;
		double dy = c.y - p->y;
		double centerDistSquared = dx * dx + dy * dy;
		
		if (centerDistSquared < minDistance) {
			minDistance = centerDistSquared;
			closestPoint = p;
		}
	}




	return false;
}

CollisionInformation* CollisionManager::isColliding(Polygon* p1, Circle* c2)
{
	return false;
}