#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <string>
#include <exception>

class VecDifferentSizes : std::logic_error
{
	const std::string whatStr = "olala";
public:
	VecDifferentSizes() : std::logic_error(whatStr.c_str()) {}
	virtual const char* what() const { return whatStr.c_str(); }
};

#endif // !_EXCEPTIONS_H_
