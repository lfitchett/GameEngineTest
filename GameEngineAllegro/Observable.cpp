#pragma once

#include "pch.h"

class Observable {
protected:
	std::unordered_map<int, std::function<void()>> currentSubscriptions;
	int nextKey = 1;
	friend class Subscription;

public:
	virtual void on()
	{
		for (auto subscription : currentSubscriptions) {
			subscription.second();
		}
	}

	virtual ~Observable() {};
};

class Subscription {
private:
	int id;
	Observable& observe;

public:
	Subscription(const Subscription&) = delete; // non construction-copyable
	Subscription& operator=(const Subscription&) = delete; // non copyable

	Subscription(Observable& observable, std::function<void()> func) : observe(observable)
	{
		id = observe.nextKey++;
		observe.currentSubscriptions[id] = func;
	}

	Subscription(Subscription&& o) : observe(o.observe)
	{
		id = o.id;
		o.id = 0;
	}

	Subscription& operator=(Subscription&& o)
	{
		id = o.id;
		o.id = 0;
	}

	~Subscription()
	{
		observe.currentSubscriptions.erase(id);
	}
};
