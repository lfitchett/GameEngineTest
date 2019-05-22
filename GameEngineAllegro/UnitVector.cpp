#pragma once

#include "pch.h"

#include "Vector.cpp"
#include <math.h>

class UnitVector : public Vector
{
public:
	UnitVector(const Vector& v)
	{
		float invMag = inv_square(v.x * v.x + v.y * v.y);
		x = v.x * invMag;
		y = v.y * invMag;
	}

private:
	float inv_square(float a)
	{
		// TODO: https://en.wikipedia.org/wiki/Fast_inverse_square_root
		return 1 / sqrtf(a);
	}
};