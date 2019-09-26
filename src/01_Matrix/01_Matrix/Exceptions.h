#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_
#include <string>
#include <exception>

class VectorDifferentSizes
{
	const std::string whatStr = "Vectors have different sizes.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class VectorInvalidSize
{
	const std::string whatStr = "Vector cannot have that size.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class VectorInvalidIndex
{
	const std::string whatStr = "Vector does not have element with that index.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixDifferentSizes : VectorDifferentSizes
{
	const std::string whatStr = "Matrixes have different sizes.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixInvalidSize : VectorInvalidSize
{
	const std::string whatStr = "Matrix cannot have that size.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixInvalidIndex : VectorInvalidIndex
{
	const std::string whatStr = "Matrix does not have element with that index.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

class MatrixNonConvertible
{
	const std::string whatStr = "Vector is non-convertible into matrix.";
public:
	virtual const char* what() const { return whatStr.c_str(); }
};

#endif // !_EXCEPTIONS_H_
