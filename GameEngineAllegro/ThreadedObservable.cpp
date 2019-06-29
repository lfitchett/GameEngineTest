#pragma once

#include "pch.h"

#include "Observable.cpp"

class ThreadedObservable : public Observable {
private:
	std::thread threads[10];

	std::mutex currentMux;
	std::unordered_map<int, std::function<void()>>::iterator current;

	std::mutex waitForNextLoopMux;
	std::condition_variable waitForNextLoopCV;

	std::mutex loopFinishedMux;
	std::condition_variable loopFinishedCV;

public:
	ThreadedObservable() 
	{
		for (auto& thread : threads) {
			thread = std::thread(&ThreadedObservable::callNext, this);
			//thread.detach();
		}
	}

	void on() override {
		{
			std::lock_guard<std::mutex> lock(currentMux);
			current = currentSubscriptions.begin();
		}
		waitForNextLoopCV.notify_all();
		{
			std::unique_lock<std::mutex> lock(loopFinishedMux);
			loopFinishedCV.wait(lock, [this] {
				return getNext() == nullptr;
			});
		}
	}

private:
	void callNext() 
	{
		std::function<void()>* func;
		while (true) {
			{
				std::unique_lock<std::mutex> lock(waitForNextLoopMux);
				waitForNextLoopCV.wait(lock);
			}

			while (func = getNext())
			{
				func->operator();
			}

			loopFinishedCV.notify_one();
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