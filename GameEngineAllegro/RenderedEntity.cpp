#pragma once

#include "pch.h"

#include "EventLoop.cpp"

class RenderedEntity
{
private:
	Subscription subscription;
protected:
	virtual void Render() = 0;

public:
	RenderedEntity(EventLoop &loop) : subscription(loop.Subscribe([this] { Render(); }, 2)) {	};
};