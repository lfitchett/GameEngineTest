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
	Point* pEnd = pStart + n - 1;

	Point* closestPoint = nullptr;
	double minDistance = DBL_MAX;
	for (Point* p = pStart; p <= pEnd; p++) {
		double dx = c.x - p->x;
		double dy = c.y - p->y;
		double centerDistSquared = dx * dx + dy * dy;

		if (centerDistSquared < minDistance) {
			minDistance = centerDistSquared;
			closestPoint = p;
		}
	}

	Vector projAxis(c, *closestPoint);

	/* Find min and max magnitude of each point projected onto the axis */
	float mag = Vector(c).ProjectOnto(projAxis).MagSquared();

	float cMax = sqrt(mag) + r;
	float cMin = sqrt(mag) - r;
	cMax = cMax * cMax;
	cMin = cMin * cMin;

	float pMax = 0, pMin = FLT_MAX;
	for (Point* p = pStart; p < pEnd; p++) {
		float mag = Vector(*p).ProjectOnto(projAxis).MagSquared();
		pMax = std::max(pMax, mag);
		pMin = std::min(pMin, mag);
	}

	/* Gap found, no collision */
	if (cMin > pMax || pMin > cMax) {
		return false;
	}

	/* Find the minimum overlap */
	float diff1 = cMax - pMin;
	float diff2 = pMax - cMin;
	double minOverlap;
	if (diff1 < diff2)
	{
		minOverlap = sqrt(cMax) - sqrt(pMin);
	}
	else
	{
		minOverlap = sqrt(pMax) - sqrt(cMin);
	}

	Point* x = closestPoint == pStart ? pEnd : closestPoint - 1;
	Point* y = closestPoint == pEnd ? pStart : closestPoint + 1;
	Vector direction;
	if (Vector(c, *x).MagSquared() < Vector(c, *y).MagSquared()) {
		direction = Vector(*y, *closestPoint).Inv();
	}
	else {
		direction = Vector(*closestPoint, *x);
	}

	return new CollisionInformation{
			direction,
			1
	};
}

CollisionInformation* CollisionManager::isColliding(Polygon* p1, Circle* c2)
{
	return false;
}