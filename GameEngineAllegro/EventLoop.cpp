#pragma once

#include "pch.h"

#include <mutex>
#include <thread>

#include "EventNode.cpp"

#define EventId EventNode*

constexpr size_t NUM_PRIORITIES = 3;
constexpr int FPS_TARGET = 60;

class EventLoop
{
private:
	EventNode* head[NUM_PRIORITIES];
	bool isLooping;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	EventNode* currentNode = nullptr;
	size_t currentPriority = 0;

public:
	EventLoop() : timer{ al_create_timer(1.0 / FPS_TARGET) }, event_queue{ al_create_event_queue() }
	{
		if (!timer) {
			printf("failed to create timer!\n");
		}
		if (!event_queue) {
			printf("failed to create event_queue!\n");
		}

		al_register_event_source(event_queue, al_get_timer_event_source(timer));

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
		al_start_timer(timer);

		ALLEGRO_EVENT ev;
		std::thread threads[10];
		while (isLooping)
		{
			al_wait_for_event(event_queue, &ev);
			al_flush_event_queue(event_queue);

			currentNode = nullptr;
			currentPriority = 0;
			for (auto& thread : threads) {
				thread = std::thread(&EventLoop::callNext, this);
			}

			for (auto& thread : threads) {
				thread.join();
			}

			/* Allegro shares a global var, so call the render stuff here */
			EventNode* current = head[NUM_PRIORITIES - 1];
			while (current)
			{
				current->Func();
				current = current->Child;
			}
		}
	}

	void Stop()
	{
		al_stop_timer(timer);
		isLooping = false;
	}

	~EventLoop()
	{
		EventNode* current;
		for (size_t i = 0; i < NUM_PRIORITIES; i++) {
			current = head[i];
			while (current)
			{
				EventNode* toDelete = current;
				current = current->Child;
				delete toDelete;
			}
		}

		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
	}

private:
	std::mutex getNextMux;

	EventNode* getNextEvent()
	{
		EventNode* result;
		getNextMux.lock();

		if (currentNode == nullptr) {
			/* Allegro shares a global var, so don't call the render stuff in a seperate thread */
			if (currentPriority < NUM_PRIORITIES - 1) {
				/* Get next priority head */
				currentNode = head[currentPriority++];
				result = currentNode;
				currentNode = currentNode->Child;
			}
			else {
				/* Done, return null */
				result = nullptr;
			}
		}
		else {
			/* Traverse list normally */
			result = currentNode;
			currentNode = currentNode->Child;
		}

		getNextMux.unlock();
		return result;
	}

	void callNext()
	{
		EventNode* event;
		while (event = getNextEvent()) {
			event->Func();
		}
	}
};