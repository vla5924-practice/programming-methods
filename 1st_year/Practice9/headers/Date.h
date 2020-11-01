#ifndef _TODOLIST_DATE_H_
#define _TODOLIST_DATE_H_
#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions.h"

namespace TodoList
{
	class date
	{
		unsigned d, m, y;
		unsigned fix_day(unsigned);
	public:
		date();
		date(const date&);
		date(unsigned, unsigned, unsigned);
		~date();

		bool bissextile() const;
		unsigned day() const;
		unsigned month() const;
		unsigned year() const;

		date& operator()(unsigned, unsigned, unsigned);
		unsigned operator[](char field) const;
		const date& operator=(const date&);

		bool operator==(const date&) const;
		bool operator!=(const date&) const;
		bool operator>(const date&) const;
		bool operator>=(const date&) const;
		bool operator<(const date&) const;
		bool operator<=(const date&) const;

		friend std::ostream& operator<<(std::ostream&, const date&);
		operator std::string();
	};

	namespace date_exception
	{
		class bad_day : public exception_uint
		{
		public:
			bad_day(unsigned);
		};

		class bad_month : public exception_uint
		{
		public:
			bad_month(unsigned);
		};

		class bad_year : public exception_uint
		{
		public:
			bad_year(unsigned);
		};
	}
}

#endif