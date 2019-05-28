/* Based on https://www.sevenson.com.au/actionscript/sat/ */

#include "pch.h"
#include "CollisionManager.h"

double FindOverlap(Point* p1, Point* p2, size_t n1, size_t n2, Vector& axis);

CollisionInformation* CollisionManager::isColliding(Polygon* poly1, Polygon* poly2)
{
	/* Check outside bounds */
	Point c1 = poly1->GetCenter();
	Point c2 = poly2->GetCenter();
	if (((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y)) > ((poly1->Radius + poly2->Radius) * (poly1->Radius + poly2->Radius))) {
		return false;
	}

	Point* p1 = poly1->GetPoints();
	Point* p2 = poly2->GetPoints();
	size_t n1 = poly1->GetNumPoints();
	size_t n2 = poly2->GetNumPoints();

	Vector collisionAngle(0, 0);
	double minOverlap = DBL_MAX;
	/* Check first shape */
	for (Point* p = p1; p < p1 + n1 - 1; p++) {
		/* Find normal vector */
		Vector axis = Vector(*p, *(p + 1)).ToNorm();

		float overlap = FindOverlap(p1, p2, n1, n2, axis);
		if (overlap == 0) {
			/* Gap found */
			return false;
		}

		if (overlap < minOverlap) {
			minOverlap = overlap;
			collisionAngle = axis;
		}
	}
	/* Check second shape */
	for (Point* p = p2; p < p2 + n2 - 1; p++) {
		/* Find normal vector */
		Vector axis = Vector(*p, *(p + 1)).ToNorm();

		float overlap = FindOverlap(p1, p2, n1, n2, axis);
		if (overlap == 0) {
			/* Gap found */
			return false;
		}

		if (overlap < minOverlap) {
			minOverlap = overlap;
			collisionAngle = axis;
		}
	}

	return new CollisionInformation{
			Point(poly2->GetCenter()),
			collisionAngle,
			minOverlap,
			true
	};
}

double FindOverlap(Point* p1, Point* p2, size_t n1, size_t n2, Vector& axis) {

	/* Find min and max magnitude of each point projected onto the axis */
	float max1 = 0, min1 = FLT_MAX, max2 = 0, min2 = FLT_MAX;
	for (size_t i = 0; i < n1; i++) {
		float mag = Vector(*(p1 + i)).ProjectOnto(axis).MagSquared();
		max1 = std::max(max1, mag);
		min1 = std::min(min1, mag);
	}
	for (size_t i = 0; i < n2; i++) {
		float mag = Vector(*(p2 + i)).ProjectOnto(axis).MagSquared();
		max2 = std::max(max2, mag);
		min2 = std::min(min2, mag);
	}

	/* Find the minimum positive gap */
	float diff1 = max1 - min2;
	float diff2 = max2 - min1;
	if (diff1 > 0 && (diff2 < 0 || diff1 < diff2))
	{
		return sqrt(max1) - sqrt(min2);
	}
	else if (diff2 > 0)
	{
		return sqrt(max2) - sqrt(min1);
	}
	else
	{
		return 0;
	}
}