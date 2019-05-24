/* Based on https://www.sevenson.com.au/actionscript/sat/ */

#include "pch.h"
#include "CollisionManager.h"

double FindOverlap(Point** p1, Point** p2, size_t n1, size_t n2, Vector& axis);

CollisionInformation* CollisionManager::isColliding(Polygon* poly1, Polygon* poly2)
{
	/* Check outside bounds */
	Point c1 = poly1->GetCenter();
	Point c2 = poly2->GetCenter();
	if (((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y)) > ((poly1->Radius + poly2->Radius) * (poly1->Radius + poly2->Radius))) {
		return false;
	}

	Point** p1 = poly1->GetPoints();
	Point** p2 = poly2->GetPoints();
	size_t n1 = poly1->GetNumPoints();
	size_t n2 = poly2->GetNumPoints();
	
	Vector collisionAngle(0,0);
	double minOverlap = 0;
	/* Check first shape */
	for (size_t i = 0; i < n1 - 1; i++) {
		/* Find normal vector */
		Vector axis = Vector(*p1[i], *p1[i + 1]).ToNorm();

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
	for (size_t i = 0; i < n2 - 1; i++) {
		/* Find normal vector */
		Vector axis = Vector(*p2[i], *p2[i + 1]).ToNorm();

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

double FindOverlap(Point** p1, Point** p2, size_t n1, size_t n2, Vector& axis) {

	/* Find min and max magnitude of each point projected onto the axis */
	float max1 = FLT_MAX, min1 = 0, max2 = FLT_MAX, min2 = 0;
	for (size_t i = 0; i < n1; i++) {
		float mag = Vector(*p1[i]).ProjectOnto(axis).MagSquared();
		max1 = std::max(max1, mag);
		min1 = std::min(min1, mag);
	}
	for (size_t i = 0; i < n2; i++) {
		float mag = Vector(*p2[i]).ProjectOnto(axis).MagSquared();
		max2 = std::max(max2, mag);
		min2 = std::min(min2, mag);
	}

	float overlap = std::max(min1 - max2, min2 - max1);

	if (overlap < 0) {
		/* Gap found, no overlap */
		return 0;
	}
	else {
		return overlap;
	}
}