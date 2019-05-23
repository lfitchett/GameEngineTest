#pragma once

#include "pch.h"

#include "Point.cpp"

class Vector
{
protected:
	Vector() {}

public:
	float x;
	float y;

	Vector(float x, float y) : x(x), y(y) {}
	Vector(Point p1, Point p2) : x(p1.x - p2.x), y(p1.y - p2.y) {}

	Vector operator+(const Vector& b)
	{
		return Vector{ x + b.x, y + b.y };
	}

	Vector operator-(const Vector& b)
	{
		return Vector{ x - b.x, y - b.y };
	}

	float operator*(const Vector& b)
	{
		return x * b.x + y * b.y;
	}

	Vector operator*(float s)
	{
		return Vector(x*s, y*s);
	}

	Vector ToNorm()
	{
		return Vector{ -y, x };
	}
};