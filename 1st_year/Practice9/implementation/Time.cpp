#include "../headers/Time.h"

TodoList::time::time()
{
	this->m = 0U;
}

TodoList::time::time(unsigned h, unsigned m)
{
	this->m = 0U;
	if (h > 23U)
	{
		throw time_exception::bad_hour(h);
	}
	if (m > 59U)
	{
		throw time_exception::bad_min(m);
	}
	this->m = 60U * h + m;
}

TodoList::time::time(unsigned m)
{
	this->m = 0U;
	if (m > 1440U)
	{
		throw time_exception::bad_mins(m);
	}
	this->m = m;
}

TodoList::time::time(float mask)
{
	this->m = 0U;
	if ((mask < 00.00f) || (mask > 23.59f))
		throw time_exception::bad_mask(mask);
	int imask = (int)(mask * 100);
	set_hour(imask / 100);
	set_min(imask % 100);
}

TodoList::time& TodoList::time::set_hour(unsigned h)
{
	if (h > 23U)
		throw time_exception::bad_hour(h);
	this->m = h * 60U + min();
	return *this;
}

TodoList::time& TodoList::time::set_min(unsigned m)
{
	if (m > 59U)
		throw time_exception::bad_min(m);
	this->m = hour() * 60U + m;
	return *this;
}

unsigned TodoList::time::hour() const
{
	return m / 60U;
}

unsigned TodoList::time::min() const
{
	return m % 60U;
}

unsigned TodoList::time::get_mins() const
{
	return m;
}

TodoList::time& TodoList::time::operator()(unsigned h, unsigned m)
{
	set_hour(h);
	set_min(m);
	return *this;
}

bool TodoList::time::operator==(const time& t) const
{
	return this->m == t.m;
}

bool TodoList::time::operator!=(const time& t) const
{
	return !(*this == t);
}

bool TodoList::time::operator>(const time& t) const
{
	return this->m > t.m;
}

bool TodoList::time::operator>=(const time& t) const
{
	return (*this == t) || (*this > t);
}

bool TodoList::time::operator<(const time& t) const
{
	return this->m < t.m;
}

bool TodoList::time::operator<=(const time& t) const
{
	return (*this == t) || (*this < t);
}

const TodoList::time& TodoList::time::operator=(const time& t)
{
	this->m = t.m;
	return *this;
}

TodoList::time TodoList::time::operator+(const time& t) const
{
	time result(*this);
	unsigned tmp = this->m + t.m;
	result.m = tmp > 1440 ? tmp % 1440 : tmp;
	return result;
}

TodoList::time TodoList::time::operator-(const time& t) const
{
	time result(*this);
	unsigned tmp = this->m - t.m;
	result.m = tmp > 1440 ? 1440 - (UINT16_MAX - tmp) % 1440 : tmp;
	return result;
}

const TodoList::time& TodoList::time::operator+=(const time& t)
{
	*this = *this + t;
	return *this;
}

const TodoList::time& TodoList::time::operator-=(const time& t)
{
	*this = *this - t;
	return *this;
}

TodoList::time::operator std::string()
{
	::std::string result = "";
	if (hour() < 10)
		result += '0';
	result += std::to_string(hour());
	result += ':';
	if (min() < 10)
		result += '0';
	result += std::to_string(min());
	return result;
}

std::ostream& TodoList::operator<<(std::ostream& out, const time& t)
{
	out << t.hour() << ':' << t.min();
	return out;
}

TodoList::time_exception::bad_hour::bad_hour(unsigned value) : exception_uint("Incorrect hours.", value)       {}
TodoList::time_exception::bad_min::bad_min(unsigned value)   : exception_uint("Incorrect minutes.", value)     {}
TodoList::time_exception::bad_mins::bad_mins(unsigned value) : exception_uint("Incorrect timestamp.", value)   {}
TodoList::time_exception::bad_mask::bad_mask(float value)    : exception_float("Incorrect float mask.", value) {}