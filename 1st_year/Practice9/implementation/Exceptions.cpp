#include "../headers/Exceptions.h"

TodoList::exception::exception() : std::invalid_argument(nullptr)
{
	this->what_str = "Unknown todolist error.";
}

TodoList::exception::exception(std::string what_str) : std::invalid_argument(nullptr)
{
	this->what_str = what_str;
}

const char* TodoList::exception::what() const
{
	return this->what_str.c_str();
}

TodoList::exception_uint::exception_uint()
{
	this->value = 0U;
}

TodoList::exception_uint::exception_uint(unsigned value)
{
	this->value = value;
}

TodoList::exception_uint::exception_uint(std::string what_str, unsigned value) : exception(what_str)
{
	this->value = value;
}

TodoList::exception_float::exception_float()
{
	this->value = 0.f;
}

TodoList::exception_float::exception_float(float value)
{
	this->value = value;
}

TodoList::exception_float::exception_float(std::string what_str, float value) : exception(what_str)
{
	this->value = value;
}

TodoList::exception_string::exception_string()
{
	this->value = "";
}

TodoList::exception_string::exception_string(std::string value)
{
	this->value = value;
}

TodoList::exception_string::exception_string(std::string what_str, std::string value) : exception(what_str)
{
	this->value = value;
}
