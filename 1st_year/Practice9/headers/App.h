#ifndef _TODOLIST_APP_H_
#define _TODOLIST_APP_H_
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include "TaskStd.h"
#include "Exceptions.h"

namespace TodoList
{
	class app
	{
		std::list<ctask*> tasks;
		size_t tcount;
		std::string filename;
		std::list<ctask*>::iterator get_before_date(date);
	public:
		app();
		~app();

		bool add(const std::string&, task::type, date);
		bool add(const std::string&, date, time, time);
		bool add(const std::string&, date);
		bool remove(ctask*);
		bool remove(unsigned);

		void print() const;
		void print(date) const;
		void print(unsigned) const;
		std::string get_filename() const;

		bool open(const std::string&);
		bool create(const std::string&);
		bool save();

		void start();
		void reset();
	};

	namespace app_exception
	{
		class parsing : public exception_string
		{
		public:
			parsing(std::string);
		};

		class file_open : public exception_string
		{
		public:
			file_open(std::string);
		};

		class file_write : public exception_string
		{
		public:
			file_write(std::string);
		};

		class bad_uid : public exception_uint
		{
		public:
			bad_uid(unsigned);
		};
	}
}

#endif