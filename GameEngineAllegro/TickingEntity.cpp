#pragma once

#include "pch.h"

#include "EventLoop.cpp"

template <EventPriority priority>
class TickingEntity
{
private:
	Subscription subscription;

protected:
	virtual void Tick() = 0;

public:
	TickingEntity(EventLoop &loop) : subscription(loop.Subscribe([this] { Tick(); }, priority)) {	};
};