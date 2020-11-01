#include <iostream>
#include "Vector.h"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	size_t dims = 0;

	std::cout << "Введите размер первого вектора: ";
	std::cin >> dims;
	Vector v1(dims);
	std::cout << "Введите координаты вектора (через пробел): ";
	v1.input();
	v1.print();
	std::cout << "\n";
	Vector v3;

	std::cout << "Длина: " << v1.len() << "\n";

	std::cout << "Умнож на -1: ";
	try
	{
		v3 = v1 * -1;
		v3.print();
		std::cout << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Сумма с 1: ";
	try
	{
		v3 = v1 + 1;
		v3.print();
		std::cout << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Разность с 1: ";
	try
	{
		v3 = v1 - 1;
		v3.print();
		std::cout << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Введите размер второго вектора: ";
	std::cin >> dims;
	Vector v2(dims);
	std::cout << "Введите координаты вектора (через пробел): ";
	v2.input();
	v2.print();
	std::cout << "\n";

	std::cout << "Сумма: ";
	try
	{
		v3 = v1 + v2;
		v3.print();
		std::cout << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Разность: ";
	try
	{
		v3 = v1 - v2;
		v3.print();
		std::cout << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Скалярное произведение: ";
	try
	{
		double scal = 0.F;
		scal = v1 * v2;
		std::cout << scal << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}

	std::cout << "Угол в радианах: ";
	try
	{
		double ang = 0.F;
		ang = v1.angle(v2);
		std::cout << ang << "\n";
	}
	catch (VectorUnequalDimensionException)
	{
		std::cout << "Размеры не совпадают\n";
	}
}