#pragma once

#include <string>

namespace Core
{
	class EventException
	{
	private:
		std::string where;
		std::string what;
		int16_t	code;

	public:
		EventException()
			: where(), what(), code(-201)
		{	}

		EventException(const std::string& where, const std::string& what, int16_t code)
			: where(where), what(what), code(code)
		{	}

	public:
		int16_t Code() const { return code; }
		const std::string& What() const { return what; }
		const std::string& Where() const { return where; }

	public:
		virtual ~EventException() = default;
	};
}