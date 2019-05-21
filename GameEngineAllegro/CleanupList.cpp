#pragma once

#include "pch.h"
#include <typeinfo>

class IDisposable
{
public:
	virtual ~IDisposable() = 0;
};

class CleanupList
{
private:
	struct CleanupNode
	{
		CleanupNode *child;
		IDisposable* data;

		CleanupNode(IDisposable* data)
		{
			this->data = data;
			this->child = nullptr;
		}
	};

	CleanupNode *head = nullptr;

public:
	void Add(IDisposable* item)
	{
		if (!head)
		{
			head = new CleanupNode(item);
		}
		else
		{
			CleanupNode* newNode = new CleanupNode(item);
			newNode->child = head;
			head = newNode;
		}
	}

	void Cleanup()
	{
		CleanupNode *current = head;
		while (current)
		{
			printf("Cleaning up %s.", typeid(current->data).name());

			CleanupNode *next = current->child;
			delete current->data;
			delete current;
			current = next;
		}

		head = nullptr;
	}

	~CleanupList() {
		Cleanup();
	}
};
