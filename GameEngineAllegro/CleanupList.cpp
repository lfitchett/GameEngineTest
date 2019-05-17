#pragma once

#include "pch.h"

template <typename T>
class CleanupList
{
private:
	struct SingleNode
	{
		SingleNode *child;
		T data;

		SingleNode(T data)
		{
			this->data = data;
			this->child = nullptr;
		}
	};

	SingleNode *head;
	SingleNode *tail;

public:
	CleanupList<T>() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	void Add(T item)
	{
		if (!this->head)
		{
			this->head = new SingleNode(item);
			this->tail = this->head;
		}
		else
		{
			this->tail->child = new SingleNode(item);
			this->tail = this->tail->child;
		}
	}

	void Cleanup()
	{
		SingleNode *current = this->head;
		while (current)
		{
			SingleNode *next = current->child;
			delete current->data;
			delete current;
			current = next;
		}

		this->head = nullptr;
		this->tail = nullptr;
	}

	~CleanupList() {
		this->Cleanup();
	}
};
