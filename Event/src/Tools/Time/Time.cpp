#include "Time.h"

namespace Core
{
	Time::Time()
		: time(clock_t::now())
	{	}

	Time::Time(const std::chrono::duration<long long, std::nano>& time)
		: time(time)
	{	}

	Time& Time::GetTime() 
	{
		return *this;
	}

	void Time::SetTime(const std::chrono::time_point<clock_t>& time)
	{
		this->time = time;
	}

	double Time::AsSeconds()
	{
		return std::chrono::duration_cast<seconds>(time.time_since_epoch()).count();
	}

	double Time::AsMilliseconds()
	{
		return std::chrono::duration_cast<milliseconds>(time.time_since_epoch()).count();
	}

	double Time::AsNanoseconds()
	{
		return std::chrono::duration_cast<nanoseconds>(time.time_since_epoch()).count();
	}

	double Time::AsMicroseconds()
	{
		return std::chrono::duration_cast<microseconds>(time.time_since_epoch()).count();
	}

	double Time::AsMinutes()
	{
		return std::chrono::duration_cast<minutes>(time.time_since_epoch()).count();
	}

	double Time::AsHours()
	{
		return std::chrono::duration_cast<hours>(time.time_since_epoch()).count();
	}

	Time Time::operator-(const Time& other)
	{
		return Time(time - other.time);
	}

	Time Time::operator+(const Time& other)
	{
		return Time(time.time_since_epoch() + other.time.time_since_epoch());
	}
}