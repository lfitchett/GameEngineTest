#include "pch.h"

class EventNode
{
public:
	EventNode *Parent;
	EventNode *Child;

	std::function<void()> Func;

	EventNode(std::function<void()> func)
	{
		this->Func = func;

		this->Parent = nullptr;
		this->Child = nullptr;
	}

	~EventNode()
	{
		if (this->Parent)
		{
			this->Parent->Child = this->Child;
		}

		if (this->Child)
		{
			this->Child->Parent = this->Parent;
		}
	}
};
