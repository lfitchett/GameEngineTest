#pragma once

#include "pch.h"

#include "Vector.cpp"
#include <math.h>

class UnitVector : public Vector
{
public:
	UnitVector(const Vector& v) : UnitVector(v.x, v.y) {}

	UnitVector(const Point& p1, const Point& p2) : UnitVector(p1.x - p2.x, p1.y - p2.y) {}

	UnitVector(float x, float y)
	{
		float invMag = inv_square(x * x + y * y);
		this->x = x * invMag;
		this->y = y * invMag;
	}

	Vector Reflect(Vector& b)
	{
		UnitVector n = b.ToNorm();

		return (*this) - (n * ((*this)*n)) * 2.f;
	}

private:
	float inv_square(float a)
	{
		// TODO: https://en.wikipedia.org/wiki/Fast_inverse_square_root
		return 1 / sqrtf(a);
	}
};