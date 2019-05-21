#pragma once

#include "pch.h"

#include "EventLoop.cpp"

class RenderedEntity
{
private:
	EventId id;

protected:
	EventLoop &mainLoop;

	virtual void Render() = 0;

public:
	RenderedEntity(EventLoop &loop) : mainLoop(loop) {
		this->id = loop.Subscribe([this] {return this->Render(); });
	};

	virtual ~RenderedEntity() {
		this->mainLoop.Unsubscribe(this->id);
	}
};