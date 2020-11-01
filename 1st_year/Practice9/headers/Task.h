#ifndef _TODOLIST_TASK_H_
#define _TODOLIST_TASK_H_
#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Time.h"

namespace TodoList
{
	namespace task
	{
		enum type
		{
			t_std,
			t_day
		};
	}

	class ctask
	{
	protected:
		static unsigned uid_stream;
		unsigned uid;
	public:
		std::string title;
		date start;

		ctask();
		ctask(const ctask&);
		ctask(const std::string&);
		ctask(const std::string&, date);
		virtual ~ctask();

		unsigned get_uid() const;

		virtual void print() = 0;
		virtual void print(std::ofstream&) = 0;

		virtual bool operator>(const ctask&) const;
		virtual bool operator<(const ctask&) const;
	};
}

#endif