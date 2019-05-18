#pragma once

#include "pch.h"

class CollidableObject 
{
public:
	bool isSolid = true;
};

class NonSolidObject : public CollidableObject
{
public:
	bool isSolid = false;
};