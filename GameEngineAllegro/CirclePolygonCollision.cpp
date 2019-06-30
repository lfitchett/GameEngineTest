#include "pch.h"
#include "CollisionManager.h"

CollisionInformation* CollisionManager::isColliding(Circle& circ, Polygon& poly)
{
	/* Check outside bounds */
	if (!circ.GetBounds().intersects(poly.GetBounds())) {
		return false;
	}

	std::vector<Point>& points = poly.GetPoints();

	Point* closestPoint = nullptr;
	double minDistance = DBL_MAX;
	for (Point& p : points) {
		double dx = circ.center.x - p.x;
		double dy = circ.center.y - p.y;
		double centerDistSquared = dx * dx + dy * dy;

		if (centerDistSquared < minDistance) {
			minDistance = centerDistSquared;
			closestPoint = &p;
		}
	}

	Vector projAxis(circ.center, *closestPoint);

	/* Find min and max magnitude of each point projected onto the axis */
	float mag = sqrt(Vector(circ.center).ProjectOnto(projAxis).MagSquared());

	float cMax = mag + circ.radius;
	float cMin = mag = circ.radius;
	cMax = cMax * cMax;
	cMin = cMin * cMin;

	float pMax = 0, pMin = FLT_MAX;
	for (Point& p : points) {
		float mag = Vector(p).ProjectOnto(projAxis).MagSquared();
		pMax = std::max(pMax, mag);
		pMin = std::min(pMin, mag);
	}

	/* Gap found, no collision */
	if (cMin > pMax || pMin > cMax) {
		return false;
	}

	/* Find the minimum overlap */
	//float diff1 = cMax - pMin;
	//float diff2 = pMax - cMin;
	//double minOverlap;
	//if (diff1 < diff2)
	//{
	//	minOverlap = sqrt(cMax) - sqrt(pMin);
	//}
	//else
	//{
	//	minOverlap = sqrt(pMax) - sqrt(cMin);
	//}

	// TODO: Find direction
	return new CollisionInformation{
			Vector(),
			0
	};
}

CollisionInformation* CollisionManager::isColliding(Polygon& p1, Circle& c2)
{
	return false;
}