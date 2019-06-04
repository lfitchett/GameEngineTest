#pragma once

#include "pch.h"

#include "EventNode.cpp"

#define EventId EventNode*
#define NUM_PRIORITIES 3
constexpr int FPS_TARGET = 60;

class EventLoop
{
private:
	EventNode* head[NUM_PRIORITIES];
	bool isLooping;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

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

		EventNode *current;
		ALLEGRO_EVENT ev;

		while (isLooping)
		{
			al_wait_for_event(event_queue, &ev);

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
				current = current->Child;
				delete current;
			}
		}

		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
	}
};