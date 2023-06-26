#pragma once

#include <cstdint>
#include "../All events/IEvent.h"

namespace Core
{
	class Event
	{
	public:
		enum class EventType : int8_t
		{
			NONE = 0,
			KEY_PRESSED = 1,
			KEY_RELEASED
		};

	private:
		EventType type;
		IEvent* event;

	public:
		Event();
		Event(EventType type, IEvent* event);

	public:
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

	public:
		void Bind(EventType type, IEvent* event);

		IEvent* GetEvent();
		EventType GetType();

	public:
		~Event();
	};
}