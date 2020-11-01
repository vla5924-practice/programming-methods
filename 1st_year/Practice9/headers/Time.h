#ifndef _TODOLIST_TIME_H_
#define _TODOLIST_TIME_H_
#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"

namespace TodoList
{
	class time
	{
		unsigned m;
	public:
		time();
		time(unsigned, unsigned);
		explicit time(unsigned);
		time(float);  // ;)
		
		time& set_hour(unsigned);
		time& set_min(unsigned);

		unsigned hour() const;
		unsigned min() const;
		unsigned get_mins() const;

		time& operator()(unsigned, unsigned);

		bool operator==(const time&) const;
		bool operator!=(const time&) const;
		bool operator>(const time&) const;
		bool operator>=(const time&) const;
		bool operator<(const time&) const;
		bool operator<=(const time&) const;

		const time& operator=(const time&);
		time operator+(const time&) const;
		time operator-(const time&) const;
		const time& operator+=(const time&);
		const time& operator-=(const time&);

		friend std::ostream& operator<<(std::ostream&, const time&);
		operator std::string();
	};

	namespace time_exception
	{
		class bad_hour : public exception_uint
		{
		public:
			bad_hour(unsigned);
		};

		class bad_min : public exception_uint
		{
		public:
			bad_min(unsigned);
		};

		class bad_mins : public exception_uint
		{
		public:
			bad_mins(unsigned);
		};

		class bad_mask : public exception_float
		{
		public:
			bad_mask(float);
		};
	}
}

#endif