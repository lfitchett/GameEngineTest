#pragma once

#include "pch.h"

#include "EventLoop.cpp"

class TickingEntity
{
protected:
	EventLoop &mainLoop;
	EventId id;

	virtual void Tick() = 0;

public:
	TickingEntity(EventLoop &loop) : mainLoop(loop) {
		this->id = loop.Subscribe([this] {return this->Tick(); });
	};

	virtual ~TickingEntity() {
		this->mainLoop.Unsubscribe(this->id);
	}
};