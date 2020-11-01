#ifndef _TODOLIST_TASKSTD_H_
#define _TODOLIST_TASKSTD_H_
#include "TaskDay.h"

namespace TodoList
{
	namespace task
	{
		class std : public ctask
		{
		public:
			time t_start;
			time t_end;
			std();
			std(const std&);
			std(const ::std::string&);
			std(const ::std::string&, date);
			std(const ::std::string&, date, time, time);
			~std();

			time get_start();
			time get_end();
			time set_start(time);
			time set_end(time);

			void print();
			void print(::std::ofstream&);

			bool operator>(const day&) const;
			bool operator>(const std&) const;
			bool operator<(const day&) const;
			bool operator<(const std&) const;
		};
	}
}

#endif