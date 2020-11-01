#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "Vector.h"

void main()
{
	Vector v1, v2, v3;
	size_t dims = 0;
	double op2;
	setlocale(LC_ALL, "Russian");

	v_init(&v1);
	v_init(&v2);
	v_init(&v3);

	printf("Введите размер первого вектора: ");
	scanf("%zd", &dims);
	if (v_create(dims, &v1) == 1)
	{
		printf("Не могу создать вектор.\n");
		return;
	}
	printf("Введите координаты вектора (через пробел): ");
	v_input(v1);
	v_output(v1);
	printf("Длина: ");
	if (!v_len(v1, &op2))
		printf("%lf\n", op2);
	else
		printf("Не могу посчитать длину.\n");
	printf("Умножение на -1: ");
	if (!v_mul(v1, -1.0F, &v3))
		v_output(v3);
	else
		printf("Не могу выполнить.\n");
	printf("Введите размер второго вектора: ");
	scanf("%zd", &dims);
	if (v_create(dims, &v2) == 1)
	{
		printf("Не могу создать вектор.\n");
		return;
	}
	printf("Введите координаты вектора (через пробел): ");
	v_input(v2);
	v_output(v2);
	printf("Сумма: ");
	if(!v_add(v1, v2, &v3))
		v_output(v3);
	else
		printf("Не могу сложить (возможно, векторы разной длины).\n");
	printf("Разность: ");
	if(!v_sub(v1, v2, &v3))
		v_output(v3);
	else
		printf("Не могу вычесть (возможно, векторы разной длины).\n");
	printf("Скалярное произведение: ");
	if (!v_scm(v1, v2, &op2))
		printf("%lf\n", op2);
	else
		printf("Не могу вычислить (возможно, векторы разной длины).\n");
	printf("Угол (в рад): ");
	if (!v_ang(v1, v2, &op2))
		printf("%lf\n", op2);
	else
		printf("Не могу посчитать угол (возможно, векторы разной длины).\n");
	printf("Угол (в градусах): ");
	if (!v_deg(v1, v2, &op2))
		printf("%lf\n", op2);
	else
		printf("Не могу посчитать угол (возможно, векторы разной длины).\n");
}
