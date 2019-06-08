/* Based on https://www.sevenson.com.au/actionscript/sat/ */

#include "pch.h"
#include "CollisionManager.h"

bool CheckVectorForGap(Point* p1, Point* p2, size_t n1, size_t n2, Vector vectorToCheck, float& minOverlap, Vector& collisionAngle);
double FindOverlap(Point* p1, Point* p2, size_t n1, size_t n2, Vector& axis);

CollisionInformation* CollisionManager::isColliding(Polygon* poly1, Polygon* poly2)
{
	/* Check outside bounds */
	RectangleBound* b1 = poly1->GetBounds();
	RectangleBound* b2 = poly2->GetBounds();
	if (!(b1->xMin < b2->xMax && b1->xMax > b2->xMin && b1->yMin < b2->yMax && b1->yMax > b2->yMin)) {
		return false;
	}

	Point* p1 = poly1->GetPoints();
	Point* p2 = poly2->GetPoints();
	size_t n1 = poly1->GetNumPoints();
	size_t n2 = poly2->GetNumPoints();

	Vector collisionAngle(0, 0);
	float minOverlap = FLT_MAX;
	/* Check first shape */
	Point* end = p1 + n1 - 1;
	for (Point* p = p1; p < end; p++) {
		if (CheckVectorForGap(p1, p2, n1, n2, Vector(*p, *(p + 1)), minOverlap, collisionAngle)) {
			return false;
		}
	}
	if (CheckVectorForGap(p1, p2, n1, n2, Vector(*p1, *end), minOverlap, collisionAngle)) {
		return false;
	}

	/* Check second shape */
	end = p2 + n2 - 1;
	for (Point* p = p2; p < end; p++) {
		if (CheckVectorForGap(p1, p2, n1, n2, Vector(*p, *(p + 1)), minOverlap, collisionAngle)) {
			return false;
		}
	}
	if (CheckVectorForGap(p1, p2, n1, n2, Vector(*p2, *end), minOverlap, collisionAngle)) {
		return false;
	}



	/* For some reason I have to do this */
	if (collisionAngle.x == 0) {
		collisionAngle.y *= -1;
	}

	return new CollisionInformation{
			collisionAngle,
			minOverlap
	};
}

bool CheckVectorForGap(Point* p1, Point* p2, size_t n1, size_t n2, Vector vectorToCheck, float& minOverlap, Vector& collisionAngle)
{
	/* Find normal vector */
	Vector axis = vectorToCheck.ToNorm();

	float overlap = FindOverlap(p1, p2, n1, n2, axis);
	if (overlap == 0) {
		/* Gap found */
		return true;
	}

	if (overlap < minOverlap) {
		minOverlap = overlap;
		collisionAngle = axis;
	}

	return false;
}

double FindOverlap(Point* p1, Point* p2, size_t n1, size_t n2, Vector& axis)
{
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

	/* Gap found, no collision */
	if (min1 > max2 || min2 > max1) {
		return 0;
	}

	/* Find the minimum overlap */
	float diff1 = max1 - min2;
	float diff2 = max2 - min1;
	if (diff1 < diff2)
	{
		axis.x *= -1;
		axis.y *= -1;
		return sqrt(max1) - sqrt(min2);
	}
	else
	{
		return sqrt(max2) - sqrt(min1);
	}

}