#pragma once

#include "pch.h"

#include "Observable.cpp"

constexpr int FPS_TARGET = 60;

class EventLoop
{
private:
	std::vector<Observable> priorities;
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
	};

	Subscription Subscribe(std::function<void()> func, uint16_t priority = 0)
	{
		return Subscription(priorities[priority], func);
	};

	void Start()
	{
		isLooping = true;
		al_start_timer(timer);
		ALLEGRO_EVENT ev;

		while (isLooping)
		{
			al_wait_for_event(event_queue, &ev);
			al_flush_event_queue(event_queue);

			for (auto priority : priorities) {
				priority.on();
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
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
	}
};