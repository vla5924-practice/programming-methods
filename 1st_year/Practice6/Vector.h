/*
 *  VECTOR.H :: Рекомендации по использованию
 * - большинство функций возвращают код выполнения: 1 в случае ошибки, 0 в случае успеха
 * - после объявления переменных типа Vector выполните инициализацию с помощью v_init()
 * - для проверки пары векторов (положительная равная размерность) используйте v_check2()
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	size_t dim;
	double* v;
} Vector;

// Инициализация
int v_init(Vector*);
// Создает вектор с заданной размерностью
int v_create(size_t, Vector*);
// Удаляет вектор
int v_destroy(Vector*);

// Выполняет сложение векторов
int v_add(Vector, Vector, Vector*);
// Умножает вектор на число
int v_mul(Vector, double, Vector*);
// Выполняет вычитание векторов
int v_sub(Vector, Vector, Vector*);
// Выполняет скалярное произведение
int v_scm(Vector, Vector, double*);

// Возвращает угол между векторами (в рад)
int v_ang(Vector, Vector, double*);
// Возвращает угол между векторами (в градусах)
int v_deg(Vector, Vector, double*);
// Возвращает длину вектора
int v_len(Vector, double*);

// Ввод значений
void v_input(Vector);
// Вывод значений
void v_output(Vector);

// Проверяет правильность
int v_check(Vector);
// Проверяет парную правильность
int v_check2(Vector, Vector);

#endif
