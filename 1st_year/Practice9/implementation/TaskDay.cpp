#include "../headers/TaskDay.h"

TodoList::task::day::day() : ctask()
{

}

TodoList::task::day::day(const ::std::string& title, date start) : ctask(title, start)
{

}

TodoList::task::day::day(const day& t) : ctask(t)
{

}

TodoList::task::day::~day()
{

}

void TodoList::task::day::print()
{
	::std::cout << '[' << uid << "] " << ::std::string(start) << ' ' << title << '\n';
}

void TodoList::task::day::print(::std::ofstream& fout)
{
	fout << "1 " << start << ' ' << title << '\n';
}
