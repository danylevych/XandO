#pragma once

#include <chrono>

namespace Core
{
	class Time
	{
	public:
		using Zero			= Time;
		using clock_t		= std::chrono::high_resolution_clock;

		using nanoseconds	= std::chrono::duration<double, std::nano>;
		using microseconds	= std::chrono::duration<double, std::micro>;
		using milliseconds	= std::chrono::duration<double, std::milli>;
		using seconds		= std::chrono::duration<double, std::ratio<1>>;
		using minutes		= std::chrono::duration<double, std::ratio<60>>;
		using hours			= std::chrono::duration<double, std::ratio<3600>>;

	private:
		friend class Clock;

	private:
		std::chrono::time_point<clock_t> time;

	public:
		Time();
		Time(const std::chrono::duration<long long, std::nano>& time);

	public:
		Time& GetTime();
		void SetTime(const std::chrono::time_point<clock_t>& time);

	public:
		double AsSeconds();
		double AsMilliseconds();
		double AsNanoseconds();
		double AsMicroseconds();
		double AsMinutes();
		double AsHours();

	public:
		Time operator-(const Time& other);
		Time operator+(const Time& other);
	};
}