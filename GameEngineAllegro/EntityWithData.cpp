#pragma once

#include "pch.h"

#include "SharedData.cpp"

class EntityWithData {
public:
	EntityWithData(SharedData &data) : sharedData(data) {};

protected:
	SharedData &sharedData;
};

	