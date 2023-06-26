#include "Event.h"

namespace Core
{
	Event::Event()
		: type(EventType::NONE),
		event(nullptr)
	{	}

	Event::Event(EventType type, IEvent* event)
		: type(type)
	{
		this->event = event;
		event = nullptr;
	}


	void Event::Bind(EventType type, IEvent* event)
	{
		delete this->event;
		this->type = type;
		this->event = event;
		event = nullptr;
	}

	IEvent* Event::GetEvent() { return event; }
	Event::EventType Event::GetType() { return type; }

	Event::~Event()
	{
		delete event;
	}
}