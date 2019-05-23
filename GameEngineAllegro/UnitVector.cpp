#pragma once

#include "pch.h"

#include "Vector.cpp"
#include <math.h>

class UnitVector : public Vector
{
public:
	UnitVector(const Vector& v) : UnitVector(v.x, v.y) {}

	UnitVector(float x, float y)
	{
		float invMag = inv_square(x * x + y * y);
		this->x = x * invMag;
		this->y = y * invMag;
	}

private:
	float inv_square(float a)
	{
		// TODO: https://en.wikipedia.org/wiki/Fast_inverse_square_root
		return 1 / sqrtf(a);
	}
};