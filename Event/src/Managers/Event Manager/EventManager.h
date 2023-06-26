#pragma once

#include "../../All events/KeyEvent.h"

namespace Core
{
	class EventManager
	{
	public:
		EventManager() = delete;
		EventManager(EventManager&& other) = delete;
		EventManager(const EventManager& other) = delete;
		EventManager& operator=(EventManager&& other) = delete;
		EventManager& operator=(const EventManager& other) = delete;
		~EventManager() = delete;

	private:
		static KeyEvent* event;
		static bool firstCalling;

	public:
		static bool PollKeyEvent(Event& e);
		static KeyEvent* ParseKeyEvent(Event& e);

	};
};