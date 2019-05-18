#include "pch.h"

#include "EntityWithData.cpp"

class Circle : public EntityWithData
{
public:
	Circle(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		printf("Making Circle\n");
	}

	~Circle() 
	{
		printf("Cleanup Circle\n");
	}

private:
	Location currLocation;

protected:
	void Tick()
	{
		sharedData.mouseLocation.print();
	}
};
