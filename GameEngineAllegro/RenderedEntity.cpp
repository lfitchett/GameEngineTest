#pragma once

#include "pch.h"

#include "EventLoop.cpp"
#include "CleanupList.cpp"

class RenderedEntity
{
private:
	EventId id;

protected:
	EventLoop &mainLoop;

	virtual void Render() = 0;

public:
	RenderedEntity(EventLoop &loop) : mainLoop(loop) {
		id = loop.Subscribe([this] { Render(); }, 2);
	};

	virtual ~RenderedEntity() {
		mainLoop.Unsubscribe(id);
	}
};