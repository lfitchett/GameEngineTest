#include "pch.h"

#include "Shape.cpp"

class Hitbox
{
public:
	Shape** Shapes;
	size_t Size;
};

template <size_t s>
class MultiHitbox : Hitbox
{
public:
	Shape* Shapes[s];
	size_t Size = s;
};

class SingleHitbox : MultiHitbox<1> {};
