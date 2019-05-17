#pragma once

#include "pch.h"

#include "EventNode.cpp"
#include "CleanupList.cpp"

#define EventId EventNode*

class EventLoop
{
private:
	EventNode *head;
	bool isLooping;

public:
	EventLoop()
	{
		this->head = nullptr;
	};

	EventId Subscribe(std::function<void()> func)
	{
		EventNode* newEvent = new EventNode(func);

		if (this->head) {
			newEvent->Child = this->head;
			this->head->Parent = newEvent;
			this->head = newEvent;
		}
		else {
			this->head = newEvent;
		}

		return newEvent;
	};

	void Unsubscribe(EventId id)
	{
		if (id == this->head) {
			this->head = id->Child;
		}

		delete id;
	}

	void Start()
	{
		this->isLooping = true;
		EventNode *current = this->head;

		while (this->isLooping && this->head)
		{
			current = this->head;
			while (current)
			{
				current->Func();
				current = current->Child;
			}
		}
	}

	void Stop()
	{
		this->isLooping = false;
	}

	~EventLoop()
	{
		EventNode* current = this->head;
		while (current)
		{
			current = current->Child;
			delete current;
		}
	}
};