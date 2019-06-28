#include "pch.h"

#include "EntityWithData.cpp"
#include "TickingEntity.cpp"

class EventListener : public EntityWithData, public TickingEntity
{
private:
	ALLEGRO_EVENT_QUEUE* eventQueue; 
	ALLEGRO_EVENT currentEvent;
	EventLoop& mainLoop;

public:
	EventListener(EventLoop &loop, SharedData &data) : mainLoop(loop), EntityWithData(data), TickingEntity(loop)
	{
		eventQueue = al_create_event_queue();
		if (!eventQueue) {
			printf("Failed to make event queue\n");
		}

		if (!al_install_mouse()) {
			printf("Failed to register mouse\n");
		}
		al_register_event_source(eventQueue, al_get_mouse_event_source());

		al_register_event_source(eventQueue, al_get_display_event_source(sharedData.display));
	}

	~EventListener()
	{
		al_destroy_event_queue(eventQueue);
	}

protected:
	void Tick() override
	{
		while (al_get_next_event(eventQueue, &currentEvent)) {
			switch (currentEvent.type)
			{
			case ALLEGRO_EVENT_MOUSE_AXES:
				sharedData.mouseLocation.x = currentEvent.mouse.x;
				sharedData.mouseLocation.y = currentEvent.mouse.y;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				this->sharedData.mouseClickLocation.x = currentEvent.mouse.x;
				this->sharedData.mouseClickLocation.y = currentEvent.mouse.y;
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				mainLoop.Stop();
				break;

			default:
				break;
			}
		}
	}
};