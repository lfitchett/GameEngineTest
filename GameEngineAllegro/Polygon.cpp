/* See https://www.sevenson.com.au/actionscript/sat/ */

#pragma once

#include "pch.h"

#include <algorithm>
#include "Point.cpp"
#include "Shape.cpp"

class Polygon : public Shape
{
public:
	virtual Point* GetPoints() = 0;
	virtual size_t GetNumPoints() = 0;
	Point Center;
	double Radius;
};

template<uint16_t s>
class SizedPolygon : public Polygon
{
private:
	Point Points[s];

public:
	SizedPolygon(int points[s][2])
	{
		int xMax = INT_MIN, xMin = INT_MAX, yMax = INT_MIN, yMin = INT_MAX;
		for (int i = 0; i < s; i++) {
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

	Point* GetPoints() override { return Points; }

	size_t GetNumPoints() override { return s; }
};

