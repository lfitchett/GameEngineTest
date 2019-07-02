#pragma once

#include "pch.h"

struct Point
{
	double x;
	double y;

	Point operator+(const Point& other)
	{
		return Point{ x + other.x, y + other.y };
	}

	Point operator-(const Point& other)
	{
		return Point{ x - other.x, y - other.y };
	}

	Point operator*(const double& scaler)
	{
		return Point{ x * scaler, y * scaler };
	}
};