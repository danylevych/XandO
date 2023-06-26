#pragma once

#include "../Time/Time.h"

namespace Core
{
	class Clock
	{
	private:
		Time previous;
		Time current;

	public:
		Clock();

	public:
		Time DeltaTime();

		Time Restart();
	};
}