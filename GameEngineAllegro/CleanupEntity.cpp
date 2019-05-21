#pragma once

#include "pch.h"

#include "TickingEntity.cpp"
#include "CleanupList.cpp"

class CleanupEntity : public TickingEntity {
	using TickingEntity::TickingEntity;

private:
	CleanupList list;

public:
	void AddToCleanup(IDisposable* item)
	{
		this->list.Add(item);
	}

protected:
	void Tick() {
		printf("Cleaning up\n");
		this->list.Cleanup();
	}
};

