#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <string>
#include <exception>

class VectorDifferentSizes : std::logic_error
{
	const std::string whatStr = "olala";
public:
	VectorDifferentSizes() : std::logic_error(whatStr.c_str()) {}
	virtual const char* what() const { return whatStr.c_str(); }
};

class VectorInvalidSize : std::logic_error
{
	const std::string whatStr = "olala";
public:
	VectorInvalidSize() : std::logic_error(whatStr.c_str()) {}
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixDifferentSizes : VectorDifferentSizes
{
	const std::string whatStr = "olala";
public:
	MatrixDifferentSizes() {}
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixInvalidSize : VectorInvalidSize
{
	const std::string whatStr = "olala";
public:
	MatrixInvalidSize() {}
	virtual const char* what() const { return whatStr.c_str(); }
};

#endif // !_EXCEPTIONS_H_
