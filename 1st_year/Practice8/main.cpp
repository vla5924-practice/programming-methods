#include <iostream>
#include "Matrix.h"

int main()
{
	double d = 0.0f;
	std::cout << "Enter number: d=";
	std::cin >> d;
	std::cout << "---------------- MATRIX 1\n";
	Matrix m1;
	m1.input();
	m1.output();

	std::cout << "---------------- MATRIX 2\n";
	Matrix m2;
	m2.input();
	m2.output();

	Matrix m3;
	std::cout << "m1 + m2:\n";
	try
	{
		m3 = m1 + m2;
		m3.output();
	}
	catch (MatrixUnequalSizes)
	{
		std::cout << "Unequal sizes.\n";
	}

	std::cout << "m1 + d:\n";
	m3 = m1 + d;
	m3.output();

	std::cout << "m1 - m2:\n";
	try
	{
		m3 = m1 - m2;
		m3.output();
	}
	catch (MatrixUnequalSizes)
	{
		std::cout << "Unequal sizes.\n";
	}

	std::cout << "m1 - d:\n";
	m3 = m1 - d;
	m3.output();

	std::cout << "m1 * m2:\n";
	try
	{
		m3 = m1 * m2;
		m3.output();
	}
	catch (MatrixProductionUndefined)
	{
		std::cout << "Bad sizes: prodiction is undefined.\n";
	}

	std::cout << "m1 * d:\n";
	m3 = m1 * d;
	m3.output();
}