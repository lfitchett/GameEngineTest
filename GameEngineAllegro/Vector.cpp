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
	Vector(const Point& p) : x(p.x), y(p.y) {}
	Vector(const Point& p1, const Point& p2) : x(p1.x - p2.x), y(p1.y - p2.y) {}

	Vector operator+(const Vector& b)
	{
		return Vector{ x + b.x, y + b.y };
	}

	Vector operator-(const Vector& b)
	{
		return Vector{ x - b.x, y - b.y };
	}

	// Dot Product
	float operator*(const Vector& b)
	{
		return x * b.x + y * b.y;
	}

	// Scaler Multiplication
	Vector operator*(float s)
	{
		return Vector(x*s, y*s);
	}

	Vector ToNorm()
	{
		return Vector{ -y, x };
	}

	Vector ProjectOnto(Vector& v)
	{
		return v * (((*this) * v) / (v.x*v.x + v.y*v.y));
	}

	float MagSquared()
	{
		return x * x + y * y;
	}

	void print()
	{
		printf("x: %f, y:%f\n", x, y);
	}
};