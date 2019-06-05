#pragma once

#include "pch.h"

#include "Shape.cpp"

class Hitbox
{
public:
	bool isMoving;
	virtual Shape** GetShapes() { return NULL; };
	virtual size_t GetSize() { return 0; }

	Hitbox(bool isMoving) : isMoving(isMoving) {};

	virtual ~Hitbox() {};
};

template <size_t s>
class MultiHitbox : public Hitbox
{
protected:
	Shape* Shapes[s];
	MultiHitbox(bool isMoving) : Hitbox(isMoving) {}

public:
	Shape** GetShapes() { return Shapes; }
	size_t GetSize() { return s; }

	MultiHitbox(Shape* shapes[s], bool isMoving) : Hitbox(isMoving) {
		for (size_t i = 0; i < s; i++) {
			Shapes[i] - shapes[i];
		}
	}

	~MultiHitbox()
	{
		for (size_t i = 0; i < s; i++) {
			delete Shapes[i];
		}
	}
};

class SingleHitbox : public MultiHitbox<1>
{
public:
	SingleHitbox(Shape* shape, bool isMoving) : MultiHitbox<1>(isMoving)
	{
		Shapes[0] = shape;
	}
};
