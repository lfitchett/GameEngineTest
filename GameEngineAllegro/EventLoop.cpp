#pragma once

#include "pch.h"

#include "EventNode.cpp"
#include "CleanupList.cpp"

#define EventId EventNode*
#define NUM_PRIORITIES 2

class EventLoop
{
private:
	EventNode* head[NUM_PRIORITIES];
	bool isLooping;

public:
	EventLoop()
	{
		for (size_t i = 0; i < NUM_PRIORITIES; i++) {
			head[i] = nullptr;
		}
	};

	EventId Subscribe(std::function<void()> func, uint16_t priority = 0)
	{
		EventNode* newEvent = new EventNode(func);

		if (head[priority]) {
			newEvent->Child = head[priority];
			head[priority]->Parent = newEvent;
			head[priority] = newEvent;
		}
		else {
			head[priority] = newEvent;
		}

		return newEvent;
	};

	void Unsubscribe(EventId id)
	{
		for (size_t i = 0; i < NUM_PRIORITIES; i++) {
			if (id == head[i]) {
				head[i] = id->Child;
			}
		}

		delete id;
	}

	void Start()
	{
		isLooping = true;
		EventNode *current;

		while (isLooping)
		{
			for (size_t i = 0; i < NUM_PRIORITIES; i++) {
				current = head[i];
				while (current)
				{
					current->Func();
					current = current->Child;
				}
			}
		}
	}

	void Stop()
	{
		this->isLooping = false;
	}

	~EventLoop()
	{
		EventNode* current;
		for (size_t i = 0; i < NUM_PRIORITIES; i++) {
			current = head[i];
			while (current)
			{
				current = current->Child;
				delete current;
			}
		}
	}
};