#include "Vector.h"

int v_init(Vector* vec)
{
	vec->dim = 0;
	vec->v = NULL;
	return 0;
}

int v_create(size_t _dim, Vector* result)
{
	result->dim = _dim;
	if (_dim > 0)
	{
		size_t i;
		result->v = (double*)malloc(_dim * sizeof(double));
		for (i = 0; i < _dim; i++)
			result->v[i] = 0.0F;
		return 0;
	}
	result->v = NULL;
	if (_dim == 0)
		return 2;
	else
		return 1;
}

int v_destroy(Vector * _vec)
{
	if (_vec->dim && _vec->v)
		free(_vec->v);
	_vec->dim = 0;
	_vec->v = NULL;
	return 0;
}

int v_add(Vector v1, Vector v2, Vector* result)
{
	size_t i;
	if (!v_check2(v1, v2))
		return 1;
	v_destroy(result);
	v_create(v1.dim, result);
	for (i = 0; i < v1.dim; i++)
		result->v[i] = v1.v[i] + v2.v[i];
	return 0;
}

int v_mul(Vector vec, double num, Vector* result)
{
	size_t i;
	v_destroy(result);
	v_create(vec.dim, result);
	for (i = 0; i < vec.dim; i++)
		result->v[i] = vec.v[i] * num;
	return 0;
}

int v_sub(Vector v1, Vector v2, Vector* result)
{
	size_t i;
	if (!v_check2(v1, v2))
		return 1;
	v_destroy(result);
	v_create(v1.dim, result);
	for (i = 0; i < v1.dim; i++)
		result->v[i] = v1.v[i] - v2.v[i];
	return 0;
}

int v_scm(Vector v1, Vector v2, double* result)
{
	size_t i;
	if (!v_check2(v1, v2))
	{
		return 1;
	}
	*result = 0.0F;
	for (i = 0; i < v1.dim; i++)
		*result += v1.v[i] * v2.v[i];
	return 0;
}

int v_ang(Vector v1, Vector v2, double* result)
{
	double l1, l2, scal, lens;
	if (!v_check2(v1, v2))
		return 1;
	if((v_len(v1, &l1)) || (v_len(v2, &l2)))
		return 1;
	lens = l1 * l2;
	if(v_scm(v1, v2, &scal))
		return 1;
	*result = acos(scal / lens);
	return 0;
}

int v_deg(Vector v1, Vector v2, double* result)
{
	double ang;
	const double pi = 3.141592653589793238462643383279;
	if(v_ang(v1, v2, &ang))
		return 1;
	*result = (ang * 180.0F) / pi;
	return 0;
}

int v_len(Vector vec, double* result)
{
	size_t i;
	if (!v_check(vec))
		return 1;
	*result = 0.0F;
	for (i = 0; i < vec.dim; i++)
		*result += vec.v[i] * vec.v[i];
	*result = sqrt(*result);
	return 0;
}

void v_input(Vector vec)
{
	size_t i;
	for (i = 0; i < vec.dim; i++)
		scanf("%lf", vec.v + i);
}

void v_output(Vector vec)
{
	size_t i;
	for (i = 0; i < vec.dim; i++)
		printf("%lf ", vec.v[i]);
	printf("\n");
}

int v_check(Vector vec)
{
	return vec.dim >= 0;
}

int v_check2(Vector v1, Vector v2)
{
	return (v1.dim == v2.dim) && (v1.dim >= 0) && (v2.dim >= 0);
}
