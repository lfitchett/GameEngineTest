#pragma once

#include "pch.h"

#include "EventLoop.cpp"

class TickingEntity
{
private:
	Subscription subscription;

protected:
	virtual void Tick() = 0;

public:
	TickingEntity(EventLoop &loop) : subscription(loop.Subscribe([this] { Tick(); }, 2)) {	};
};