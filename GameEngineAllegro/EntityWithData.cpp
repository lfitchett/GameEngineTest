#pragma once

#include "pch.h"

#include "TickingEntity.cpp"
#include "SharedData.cpp"

class EntityWithData : public TickingEntity {
public:
	EntityWithData(EventLoop &loop, SharedData &data) : TickingEntity(loop), sharedData(data) {};

protected:
	SharedData &sharedData;
};

	