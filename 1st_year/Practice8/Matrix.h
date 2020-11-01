#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <string>
#include <cstring>

class Matrix
{
	unsigned rows;
	unsigned cols;
	double *m;
public:
	Matrix();
	Matrix(const Matrix&);
	Matrix(unsigned, unsigned);
	Matrix(double*, unsigned, unsigned);
	~Matrix();

	void output();
	void input();

	const Matrix& operator=(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator+(double);
	Matrix operator-(const Matrix&);
	Matrix operator-(double);
	Matrix operator*(const Matrix&);
	Matrix operator*(double);
	
	double* operator[](unsigned);
};

class MatrixUnequalSizes : std::exception
{
	const std::string what_str = "Unequal sizes";
public:
	const char* what() const;
};

class MatrixProductionUndefined : std::exception
{
	const std::string what_str = "Production is undefined";
public:
	const char* what() const;
};

#endif