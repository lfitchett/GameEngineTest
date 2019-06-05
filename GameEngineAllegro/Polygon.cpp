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
	virtual Point GetCenter() = 0;
	double Radius;
};

template<uint16_t s>
class SizedPolygon : public Polygon
{
protected:
	Point Points[s];
	Point Center;

public:
	SizedPolygon(double points[s][2])
	{
		double xMax = -DBL_MAX, xMin = DBL_MAX, yMax = -DBL_MAX, yMin = DBL_MAX;
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

		Center.x = (xMax + xMin) / 2;
		Center.y = (yMax + yMin) / 2;

		Radius = sqrt((xMax - Center.x) * (xMax - Center.x) + (yMax - Center.y)*(yMax - Center.y));
	}

	Point* GetPoints() override { return (Point*)&Points; }

	size_t GetNumPoints() override { return s; }

	Point GetCenter() override { return Center; }

};

template<uint16_t s>
class MovingPolygon : public SizedPolygon<s>
{
private:
	std::function<Point()> CenterFunc;
	Point NewPoints[s];

public:
	MovingPolygon(std::function<Point()> center, double points[s][2]) : CenterFunc(center), SizedPolygon<s>(points)
	{
		for (int i = 0; i < s; i++) {
			this->Points[i].x -= this->Center.x;
			this->Points[i].y -= this->Center.y;
		}
	}

	Point GetCenter() override {
		return CenterFunc();
	}

	Point* GetPoints() override {
		Point newCenter = CenterFunc();

		for (int i = 0; i < s; i++) {
			this->NewPoints[i].x = this->Points[i].x + newCenter.x;
			this->NewPoints[i].y = this->Points[i].y + newCenter.y;
		}

		return (Point*)&this->NewPoints;
	}

};

