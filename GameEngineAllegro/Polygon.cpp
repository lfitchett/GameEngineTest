/* See https://www.sevenson.com.au/actionscript/sat/ */

#pragma once

#include "pch.h"

#include <algorithm>
#include "Point.cpp"
#include "Shape.cpp"

class Polygon : public Shape
{
public:
	virtual Point* GetPoint(size_t i) = 0;
	virtual size_t GetNumPoints() = 0;
	virtual Point* GetCenter() = 0;
	virtual double GetRadius() = 0;
};

template<uint16_t s>
class SizedPolygon : public Polygon
{
protected:
	Point Points[s];
	double Radius;
	Point Center;

public:
	SizedPolygon(int points[s][2])
	{
		int xMax = INT_MIN, xMin = INT_MAX, yMax = INT_MIN, yMin = INT_MAX;
		for (int i = 0; i < s; i++) {
			Points[i].x = points[i][0];
			Points[i].y = points[i][1];

			xMax = std::max(xMax, points[i][0]);
			xMin = std::min(xMin, points[i][0]);
			yMax = std::max(yMax, points[i][1]);
			yMin = std::min(yMin, points[i][1]);
		}

		Radius = std::max(xMax - xMin, yMax - yMin) / 2;
		Center.x = (xMax + xMin) / 2;
		Center.y = (yMax + yMin) / 2;

	};

	size_t GetNumPoints() override { return s; }
	Point* GetPoint(size_t i) override { return &Points[i]; }
	double GetRadius() override { return Radius; }
	Point* GetCenter() override { return &Center; }
};

template<uint16_t s>
class MovingPolygon : public SizedPolygon<s>
{
private:
	std::function<Point()> Center;

public:
	MovingPolygon(std::function<Point()> center, int points[s][2]) : SizedPolygon<s>(points)
	{
		Center = center;
		for (size_t i = 0; i < s; i++)
		{
			Points[i].x -= SizedPolygon<s>::Center.x;
			Points[i].y -= SizedPolygon<s>::Center.y;
		}
	}

	Point* GetCenter() override { return &Center(); }
	Point* GetPoint(size_t i) override { return Points[i]; }


};


