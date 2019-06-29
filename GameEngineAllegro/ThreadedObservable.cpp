#pragma once

#include "pch.h"

#include "Observable.cpp"

class ThreadedObservable : public Observable {
private:
	std::thread threads[10];

	std::mutex currentMux;
	std::unordered_map<int, std::function<void()>>::iterator current;

	std::mutex activeThreadMux;
	std::condition_variable loopFinishedCV;
	int activeThreads = 0;

	std::mutex waitForNextLoopMux;
	std::condition_variable waitForNextLoopCV;


	bool isAlive = true;

public:
	ThreadedObservable()
	{
		for (auto& thread : threads) {
			thread = std::thread(&ThreadedObservable::callNext, this);
		}
	}

	void on() override {
		{
			std::unique_lock<std::mutex> lock(currentMux);
			current = currentSubscriptions.begin();
		}
		waitForNextLoopCV.notify_all();
		{
			std::unique_lock<std::mutex> lock(activeThreadMux);
			loopFinishedCV.wait_for(lock, std::chrono::milliseconds(50), [this] {return activeThreads == 0; });
		}
	}

	~ThreadedObservable()
	{
		if (activeThreads != 0) {
			std::unique_lock<std::mutex> lock(activeThreadMux);
			loopFinishedCV.wait_for(lock, std::chrono::milliseconds(50), [this] {return activeThreads == 0; });
		}
		isAlive = false;
		waitForNextLoopCV.notify_all();
		for (auto& thread : threads) {
			thread.join();
		}
	}

private:
	void callNext()
	{
		{
			std::unique_lock<std::mutex> lock(activeThreadMux);
			std::cout << "Making thread " << std::this_thread::get_id() << std::endl;
		}

		while (true) {
			/* Wait for signal from "on" */
			{
				std::unique_lock<std::mutex> lock(waitForNextLoopMux);
				waitForNextLoopCV.wait(lock);
				if (!isAlive) {
					return;
				}
			}

			/* increment active threads */
			{
				std::unique_lock<std::mutex> lock(activeThreadMux);
				activeThreads++;
			}

			/* call all subscribers */
			std::function<void()>* func;
			while (func = getNext())
			{
				(*func)();
			}

			/* decrement active threads. if no more active threads, signal "on" */
			{
				std::unique_lock<std::mutex> lock(activeThreadMux);
				activeThreads--;
				if (activeThreads == 0) {
					loopFinishedCV.notify_one();
				}
			}
		}
	}

	std::function<void()>* getNext()
	{
		std::lock_guard<std::mutex> lock(currentMux);
		if (current == currentSubscriptions.end()) {
			return nullptr;
		}

		return &(*current++).second;
	}
};