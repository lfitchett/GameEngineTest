#include "pch.h"

#include "EntityWithData.cpp"

class EventListener : public EntityWithData
{
private:
	ALLEGRO_EVENT_QUEUE* event_queue;

protected:
	void Tick()
	{
		ALLEGRO_EVENT* currentEvent;
		while (!al_is_event_queue_empty(event_queue)) {
			al_get_next_event(event_queue, currentEvent);

			switch (currentEvent->type)
			{
			case ALLEGRO_EVENT_MOUSE_AXES:
				sharedData.mouseLocation.x = currentEvent->mouse.x;
				sharedData.mouseLocation.y = currentEvent->mouse.y;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				this->sharedData.mouseClickLocation.x = currentEvent->mouse.x;
				this->sharedData.mouseClickLocation.y = currentEvent->mouse.y;
				break;

			default:
				break;
			}
		}
	}

public:
	EventListener(EventLoop &loop, SharedData &data) : EntityWithData(loop, data)
	{
		event_queue = al_create_event_queue();
		if (!event_queue) {
			printf("Failed to make event queue\n");
		}

		al_register_event_source(event_queue, al_get_display_event_source(sharedData.display));
	}

	~EventListener()
	{
		al_destroy_event_queue(event_queue);
	}
};