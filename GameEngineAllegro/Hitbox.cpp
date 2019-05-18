#include "pch.h"

#include "Shape.cpp"

class Hitbox
{
public:
	virtual Shape** GetShapes() { return NULL; };
	virtual size_t GetSize() { return 0; }

	virtual ~Hitbox() {};
};

template <size_t s>
class MultiHitbox : public Hitbox
{
protected:
	Shape* Shapes[s];

public:
	Shape** GetShapes() { return Shapes; }
	size_t GetSize() { return s; }

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
	SingleHitbox(Shape* shape)
	{
		Shapes[0] = shape;
	}
};
