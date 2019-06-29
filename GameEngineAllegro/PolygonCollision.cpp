/* Based on https://www.sevenson.com.au/actionscript/sat/ */

#include "pch.h"
#include "CollisionManager.h"

namespace Collisions
{
	bool CheckVectorForGap(std::vector<Point>& p1, std::vector<Point>& p2, Vector vectorToCheck, float& minOverlap, Vector& collisionAngle);
	double FindOverlap(std::vector<Point>& p1, std::vector<Point>& p2, Vector& axis);

	CollisionInformation* isColliding(Polygon& poly1, Polygon& poly2)
	{
		/* Check outside bounds */
		if (!poly1.GetBounds().intersects(poly2.GetBounds())) {
			return false;
		}

		std::vector<Point>& p1 = poly1.GetPoints();
		std::vector<Point>& p2 = poly2.GetPoints();

		Vector collisionAngle(0, 0);
		float minOverlap = FLT_MAX;

		/* Check first shape */
		std::vector<Point>::iterator p = p1.begin();
		while(p != p1.end()) {
			if (!CheckVectorForGap(p1, p2, Vector(*p, *++p), minOverlap, collisionAngle)) {
				return false;
			}
		}
		if (!CheckVectorForGap(p1, p2, Vector(*p1.end(), *p1.begin()), minOverlap, collisionAngle)) {
			return false;
		}

		/* Check second shape */
		p = p2.begin();
		while (p != p2.end()) {
			if (!CheckVectorForGap(p1, p2, Vector(*p, *++p), minOverlap, collisionAngle)) {
				return false;
			}
		}
		if (!CheckVectorForGap(p1, p2, Vector(*p2.end(), *p2.begin()), minOverlap, collisionAngle)) {
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

	bool CheckVectorForGap(std::vector<Point>& p1, std::vector<Point>& p2, Vector vectorToCheck, float& minOverlap, Vector& collisionAngle)
	{
		/* Find normal vector */
		Vector axis = vectorToCheck.ToNorm();

		float overlap = FindOverlap(p1, p2, axis);
		if (overlap == 0) {
			/* Gap found */
			return false;
		}

		if (overlap < minOverlap) {
			minOverlap = overlap;
			collisionAngle = axis;
		}

		return true;
	}

	double FindOverlap(std::vector<Point>& p1, std::vector<Point>& p2, Vector& axis)
	{
		/* Find min and max magnitude of each point projected onto the axis */
		float max1 = 0, min1 = FLT_MAX, max2 = 0, min2 = FLT_MAX;
		for (Point& p : p1) {
			float mag = Vector(p).ProjectOnto(axis).MagSquared();
			max1 = std::max(max1, mag);
			min1 = std::min(min1, mag);
		}
		for (Point& p : p2) {
			float mag = Vector(p).ProjectOnto(axis).MagSquared();
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
}