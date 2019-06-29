#pragma once

#include "pch.h"

class Observable {
protected:
	std::unordered_map<int, std::function<void()>> currentSubscriptions;
	int nextKey = 0;
	friend class Subscription;

public:
	virtual void on() 
	{
		for (auto subscription : currentSubscriptions) {
			subscription.second();
		}
	}
};

class Subscription {
private:
	int id;
	Observable& observe;

public:
	Subscription(Observable& observable, std::function<void()> func) : observe(observable) 
	{
		id = observe.nextKey++;
		observe.currentSubscriptions[id] = func;
	}

	~Subscription() 
	{
		observe.currentSubscriptions.erase(id);
	}
};
