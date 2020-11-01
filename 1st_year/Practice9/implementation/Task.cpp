#include "../headers/Task.h"

namespace TodoList
{
	unsigned ctask::uid_stream = 0;
}

TodoList::ctask::ctask()
{
	uid = ++uid_stream;
	start(1U, 1U, 1970U);
}

TodoList::ctask::ctask(const ctask& t)
{
	uid = ++uid_stream;
	title = t.title;
	start = t.start;
}

TodoList::ctask::ctask(const std::string& title)
{
	uid = ++uid_stream;
	start(1U, 1U, 1970U);
	this->title = title;
}

TodoList::ctask::ctask(const std::string& title, date start)
{
	uid = ++uid_stream;
	this->start = start;
	this->title = title;
}

TodoList::ctask::~ctask()
{

}

unsigned TodoList::ctask::get_uid() const
{
	return uid;
}

bool TodoList::ctask::operator>(const ctask& t) const
{
	return start > t.start;
}

bool TodoList::ctask::operator<(const ctask& t) const
{
	return start < t.start;
}
