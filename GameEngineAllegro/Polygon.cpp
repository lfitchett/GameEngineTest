#pragma once

#include "pch.h"

#include <algorithm>

struct Point
{
	double x;
	double y;
};

class Polygon
{
public:
	Point* Points;
	size_t NumPoints;
	Point Center;
	double Radius;
};

template<uint16_t p>
class SizedPolygon : public Polygon
{
public:
	Point Points[p];
	size_t NumPoints = p;

	SizedPolygon(int points[p][2])
	{
		int xMax = INT_MIN, xMin = INT_MAX, yMax = INT_MIN, yMin = INT_MAX;
		for (int i = 0; i < p; i++) {
			Points[i].x = points[i][0];
			Points[i].y = points[i][1];

			if (xMax < Points[i].x) {
				xMax = Points[i].x;
			}
			if (xMin > Points[i].x) {
				xMin = Points[i].x;
			}

			if (yMax < Points[i].y) {
				yMax = Points[i].y;
			}
			if (yMin > Points[i].y) {
				yMin = Points[i].y;
			}
		}

		Radius = std::max(xMax - xMin, yMax - yMin) / 2;
		Center.x = (xMax + xMin) / 2;
		Center.y = (yMax + yMin) / 2;
	}
};

