#include "pch.h"

#include "EntityWithData.cpp"

class Text : public EntityWithData
{
public:
	Text(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		
	}

	~Text() {
		printf("Cleanup Text\n");
	}

protected:
	void Tick()
	{

	}
};
