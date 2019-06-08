/* See https://www.sevenson.com.au/actionscript/sat/ */

#pragma once

#include "pch.h"

#include <algorithm>
#include "Point.cpp"
#include "Shape.cpp"

struct RectangleBound
{
	double xMax = -DBL_MAX;
	double xMin = DBL_MAX;
	double yMax = -DBL_MAX;
	double yMin = DBL_MAX;
};


class Polygon : public Shape
{
public:
	virtual Point* GetPoints() = 0;
	virtual size_t GetNumPoints() = 0;
	virtual RectangleBound* GetBounds() = 0;

	~Polygon() {}
};

template<uint16_t s>
class SizedPolygon : public Polygon
{
protected:
	Point Points[s];
	RectangleBound Bounds;

public:
	SizedPolygon(double points[s][2])
	{
		for (int i = 0; i < s; i++) {
			Points[i].x = points[i][0];
			Points[i].y = points[i][1];

			if (Bounds.xMax < Points[i].x) {
				Bounds.xMax = Points[i].x;
			}
			if (Bounds.xMin > Points[i].x) {
				Bounds.xMin = Points[i].x;
			}

			if (Bounds.yMax < Points[i].y) {
				Bounds.yMax = Points[i].y;
			}
			if (Bounds.yMin > Points[i].y) {
				Bounds.yMin = Points[i].y;
			}
		}
	}

	Point* GetPoints() override { return (Point*)&Points; }

	size_t GetNumPoints() override { return s; }

	RectangleBound* GetBounds() override { return &Bounds; }

};

template<uint16_t s>
class MovingPolygon : public SizedPolygon<s>
{
private:
	std::function<Point()> CenterFunc;
	Point NewPoints[s];
	RectangleBound NewBounds;

public:
	MovingPolygon(std::function<Point()> center, double points[s][2], Point* centerOffset = nullptr) : CenterFunc(center), SizedPolygon<s>(points)
	{
		Point baseCenter{ (SizedPolygon<s>::Bounds.xMax + SizedPolygon<s>::Bounds.xMin) / 2, (SizedPolygon<s>::Bounds.yMax + SizedPolygon<s>::Bounds.yMin) / 2 };

		for (int i = 0; i < s; i++) {
			SizedPolygon<s>::Points[i].x -= baseCenter.x;
			SizedPolygon<s>::Points[i].y -= baseCenter.y;
		}

		SizedPolygon<s>::Bounds.xMax -= baseCenter.x;
		SizedPolygon<s>::Bounds.xMin -= baseCenter.x;
		SizedPolygon<s>::Bounds.yMax -= baseCenter.y;
		SizedPolygon<s>::Bounds.yMin -= baseCenter.y;


		/*if (centerOffset) {
			double maxDistance = 0;
			for (int i = 0; i < s; i++) {
				SizedPolygon<s>::Points[i].x -= centerOffset->x;
				SizedPolygon<s>::Points[i].y -= centerOffset->y;

				double dx = SizedPolygon<s>::Points[i].x;
				double dy = SizedPolygon<s>::Points[i].y;

				maxDistance = std::max(maxDistance, dx * dx + dy * dy);
			}

			SizedPolygon<s>::Radius = sqrt(maxDistance);
		}*/
	}

	RectangleBound* GetBounds() override {
		Point newCenter = CenterFunc();

		NewBounds.xMax = SizedPolygon<s>::Bounds.xMax + newCenter.x;
		NewBounds.xMin = SizedPolygon<s>::Bounds.xMin + newCenter.x;
		NewBounds.yMax = SizedPolygon<s>::Bounds.yMax + newCenter.y;
		NewBounds.yMin = SizedPolygon<s>::Bounds.yMin + newCenter.y;


		return SizedPolygon<s>::GetBounds();
	}

	Point* GetPoints() override {
		Point newCenter = CenterFunc();

		for (int i = 0; i < s; i++) {
			NewPoints[i].x = SizedPolygon<s>::Points[i].x + newCenter.x;
			NewPoints[i].y = SizedPolygon<s>::Points[i].y + newCenter.y;
		}

		return (Point*)&NewPoints;
	}

};

