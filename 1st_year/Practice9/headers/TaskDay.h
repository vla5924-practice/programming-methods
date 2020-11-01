#ifndef _TODOLIST_TASKDAY_H_
#define _TODOLIST_TASKDAY_H_
#include "Task.h"

namespace TodoList
{
	namespace task
	{
		class day : public ctask
		{
		public:
			day();
			day(const ::std::string&, date);
			day(const day&);
			~day();
			
			void print();
			void print(::std::ofstream&);
		};
	}
}

#endif