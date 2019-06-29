#pragma once

#include "pch.h"

#include "Observable.cpp"

class ThreadedObservable : public Observable {
private:
	std::thread threads[10];

	std::mutex currentMux;
	std::unordered_map<int, std::function<void()>>::iterator current;

	std::mutex activeThreadMux;
	int activeThreads = 0;

	std::mutex waitForNextLoopMux;
	std::condition_variable waitForNextLoopCV;

	std::mutex loopFinishedMux;
	std::condition_variable loopFinishedCV;

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
			//std::cout << "Starting on" << std::endl;
			current = currentSubscriptions.begin();

			/*while (activeThreads > 0) {
				lock.unlock();
				std::this_thread::yield();
				lock.lock();
			}*/
			//std::cout << "Starting threads" << std::endl;
		}
		waitForNextLoopCV.notify_all();
		{
			std::unique_lock<std::mutex> lock(loopFinishedMux);
			loopFinishedCV.wait(lock);
			//std::cout << "All threads finished" << std::endl << std::endl;
		}
	}

	~ThreadedObservable()
	{
		{
			std::unique_lock<std::mutex> lock(loopFinishedMux);
			loopFinishedCV.wait(lock, [this] {
				std::lock_guard<std::mutex> lock(activeThreadMux);
				return activeThreads == 0;
			});
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
		std::function<void()>* func;
		while (true) {
			{
				std::unique_lock<std::mutex> lock(waitForNextLoopMux);
				waitForNextLoopCV.wait(lock);
				if (!isAlive) {
					return;
				}
			}

			{
				std::unique_lock<std::mutex> lock(activeThreadMux);
				activeThreads++;
			}


			while (func = getNext())
			{
				(*func)();
			}

			{
				std::unique_lock<std::mutex> lock(activeThreadMux);
				//std::cout << "ending thread " << std::this_thread::get_id() << std::endl;

				activeThreads--;
				if (activeThreads == 0) {
					//std::cout << "Notifying all threads finished. " << std::this_thread::get_id() << std::endl;
					lock.unlock();
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