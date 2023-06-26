#include "Clock.h"

namespace Core
{
	Clock::Clock()
		:
		previous(),
		current()
	{	}

	Time Clock::DeltaTime()
	{
		previous.time = current.time;
		current.time = Time::clock_t::now();

		return current - previous;
	}

	Time Clock::Restart()
	{
		Time tempTime = DeltaTime();
		previous = current = Time::Zero();

		return tempTime;
	}
}