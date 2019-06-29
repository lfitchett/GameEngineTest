/* See https://www.sevenson.com.au/actionscript/sat/ */

#pragma once

#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"
#include "RectangleBound.cpp"


class Polygon : public Shape
{
protected:
	std::vector<Point> points;
	RectangleBound bounds;

public:
	virtual std::vector<Point>& GetPoints() { return points; };
	virtual RectangleBound& GetBounds() { return bounds; };

	Polygon(std::vector<Point> points) : points(points)
	{
		for (Point& point : points) {
			bounds.xMax = std::max(bounds.xMax, point.x);
			bounds.xMin = std::min(bounds.xMin, point.x);
			bounds.yMax = std::max(bounds.yMax, point.y);
			bounds.yMin = std::min(bounds.yMin, point.y);
		}
	}

	virtual ~Polygon() {}
};

class MovingPolygon : public Polygon
{
private:
	Point& centerPoint;
	std::vector<Point> referancePoints;
	RectangleBound referanceBounds;

public:
	MovingPolygon(std::vector<Point> pts, Point& center) : Polygon(pts), centerPoint(center)
	{
		for (Point& point : points) {
			referancePoints.push_back(centerPoint - point);
		}

		referanceBounds.xMax = centerPoint.x - bounds.xMax;
		referanceBounds.xMin = centerPoint.x - bounds.xMin;
		referanceBounds.yMax = centerPoint.y - bounds.yMax;
		referanceBounds.yMin = centerPoint.y - bounds.yMin;
	}

	RectangleBound& GetBounds() override {
		bounds.xMax = centerPoint.x + referanceBounds.xMax;
		bounds.xMin = centerPoint.x + referanceBounds.xMin;
		bounds.yMax = centerPoint.y + referanceBounds.yMax;
		bounds.yMin = centerPoint.y + referanceBounds.yMin;

		return bounds;
	}

	std::vector<Point>& GetPoints() override {
		for (size_t i = 0; i < points.size(); i++) {
			points[i] = centerPoint + referancePoints[i];
		}

		return points;
	}

};

