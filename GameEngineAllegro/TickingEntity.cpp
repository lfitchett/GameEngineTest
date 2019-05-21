#pragma once

#include "pch.h"

#include "EventLoop.cpp"
#include "CleanupList.cpp"

class TickingEntity
{
private:
	EventId id;

protected:
	EventLoop &mainLoop;

	virtual void Tick() = 0;

public:
	TickingEntity(EventLoop &loop) : mainLoop(loop) {
		id = loop.Subscribe([this] { Tick(); });
	};

	virtual ~TickingEntity() {
		mainLoop.Unsubscribe(id);
	}
};