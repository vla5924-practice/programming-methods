#ifndef _TODOLIST_EXCEPTIONS_H_
#define _TODOLIST_EXCEPTIONS_H_
#include <string>
#include <stdexcept>

namespace TodoList
{
	class exception : public std::invalid_argument
	{
		std::string what_str;
	public:
		exception();
		exception(std::string);
		virtual const char* what() const;
	};

	class exception_uint : public exception
	{
	public:
		unsigned value;
		exception_uint();
		exception_uint(unsigned);
		exception_uint(std::string, unsigned);
	};

	class exception_float : public exception
	{
	public:
		float value;
		exception_float();
		exception_float(float);
		exception_float(std::string, float);
	};

	class exception_string : public exception
	{
	public:
		std::string value;
		exception_string();
		exception_string(std::string);
		exception_string(std::string, std::string);
	};
}

#endif