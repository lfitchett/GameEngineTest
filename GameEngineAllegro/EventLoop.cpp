#pragma once

#include "pch.h"

#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>

#include "EventNode.cpp"

#define EventId EventNode*

constexpr size_t NUM_PRIORITIES = 3;
constexpr int FPS_TARGET = 60;

class EventLoop
{
private:
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_TIMER* timer;

	EventNode* head[NUM_PRIORITIES];
	bool isLooping;
	std::thread threads[10];

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

		for (auto& thread : threads) {
			thread = std::thread(&EventLoop::callNext, this);
			//thread.detach();
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

		//ALLEGRO_EVENT ev;
		while (isLooping)
		{
			//al_wait_for_event(event_queue, &ev);
			//al_flush_event_queue(event_queue);

			{
				std::lock_guard<std::mutex> lock(currentMux);
				currentNode = nullptr;
				currentPriority = 0;
			}
			{
				std::unique_lock<std::mutex> lk(activeLoopsMux);
				activeLoops = 10;
			}
			waitForNextLoopCV.notify_all();
			{
				std::unique_lock<std::mutex> lock(loopFinishedMux);
				loopFinishedCV.wait(lock, [this] {
					std::unique_lock<std::mutex> lk(activeLoopsMux);
					printf("checking with %d loops left.\n", activeLoops);
					return activeLoops == 0;
				});
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

		for (auto& thread : threads) {
			thread.~thread();
		}
	}

private:
	std::mutex currentMux;
	EventNode* currentNode = nullptr;
	size_t currentPriority = 0;

	int activeLoops;
	std::mutex activeLoopsMux;

	std::mutex waitForNextLoopMux;
	std::condition_variable waitForNextLoopCV;

	std::mutex loopFinishedMux;
	std::condition_variable loopFinishedCV;

	EventNode* getNextEvent()
	{
		std::lock_guard<std::mutex> lock(currentMux);

		if (currentNode == nullptr) {
			/* Allegro shares a global var, so don't call the render stuff in a seperate thread */
			if (currentPriority < NUM_PRIORITIES - 1) {
				/* Get next priority head */
				currentNode = head[currentPriority++];
			}
			else {
				/* Done, return null */
				return nullptr;
			}
		}

		/* Traverse list normally */
		EventNode* result;
		result = currentNode;
		currentNode = currentNode->Child;

		return result;
	}

	std::atomic<int> tempLoopId = 0;

	void callNext()
	{
		int id = tempLoopId++;
		while (true)
		{
			{
				std::unique_lock<std::mutex> lock(waitForNextLoopMux);
				waitForNextLoopCV.wait(lock);
			}

			/*{
				std::unique_lock<std::mutex> pl(printMux);
				printf("Starting loop %d.\n", id);
			}*/

			EventNode* event;
			while (event = getNextEvent()) {
				event->Func();
			}

			/*{
				std::unique_lock<std::mutex> pl(printMux);
				printf("Ending loop %d.\n", id);
			}*/

			{
				std::unique_lock<std::mutex> lk(activeLoopsMux);
				activeLoops--;
			}
			loopFinishedCV.notify_all();
		}
	}
};