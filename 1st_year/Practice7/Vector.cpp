#include "Vector.h"

Vector::Vector()
{
	size = 0;
	v = nullptr;
}

Vector::Vector(size_t _size)
{
	size = _size;
	v = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		v[i] = 0;
	}
}

Vector::Vector(size_t n, double* a)
{
	size = n;
	v = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		v[i] = a[i];
	}
}

Vector::Vector(size_t n, double a)
{
	size = n;
	v = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		v[i] = a + 0.;
	}
}

Vector::Vector(const Vector & _v)
{
	size = _v.size;
	v = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		v[i] = _v.v[i];
	}
}

Vector::~Vector()
{
	delete[] v;
	size = 0;
}

bool Vector::nil() const
{
	for (size_t i = 0; i < size; i++)
	{
		if ((*this)[i] != 0)
			return false;
	}
	return true;
}

size_t Vector::dim() const
{
	return size;
}

double Vector::angle(const Vector& _v) const
{
	if (size != _v.size)
		throw VectorUnequalDimensionException();
	double scal = *this * _v, lens = len() * _v.len();
	if (!lens)
		throw VectorDivizionByZero();
	return acos(scal / lens);
}

void Vector::print(const char* message) const
{
	if (size)
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << v[i] << " ";
		}
	}
	else
	{
		std::cout << message;
	}

}

void Vector::input() const
{
	if (size)
		for (size_t i = 0; i < size; i++)
			std::cin >> v[i];
}

double Vector::len() const
{
	double l = 0.0;
	for (size_t i = 0; i < size; i++)
		l += i * i;
	return sqrt(l);
}

const Vector& Vector::operator=(const Vector& _v)
{
	if (&_v == this)
		return *this;
	if (size && v)
		delete[] v;
	size = _v.size;
	v = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		v[i] = _v.v[i];
	}
	return *this;
}

Vector Vector::operator+(const Vector & _v)
{
	if (size != _v.size)
		throw VectorUnequalDimensionException();
	Vector result(size);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = (*this)[i] + _v[i];
	}
	return result;
}

Vector Vector::operator-(const Vector& _v)
{
	if (size != _v.size)
		throw VectorUnequalDimensionException();
	Vector result(size);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = (*this)[i] - _v[i];
	}
	return result;
}

Vector Vector::operator+(double n)
{
	Vector result(size, n);
	result += *this;
	return result;
}

Vector Vector::operator-(double n)
{
	Vector result(size, n);
	result -= *this;
	return result;
}

double Vector::operator*(const Vector& _v) const
{
	if (size != _v.size)
		throw VectorUnequalDimensionException();
	double result = 0;
	for (size_t i = 0; i < size; i++)
	{
		result += (*this)[i] * _v[i];
	}
	return result;
}

Vector Vector::operator*(double m)
{
	Vector result(*this);
	for (size_t i = 0; i < size; i++)
	{
		result[i] *= m;
	}
	return result;
}

Vector Vector::operator/(double m)
{
	if (m == 0)
		throw VectorDivizionByZero();
	Vector result(*this);
	for (size_t i = 0; i < size; i++)
	{
		result[i] /= m;
	}
	return result;
}

bool Vector::operator==(const Vector& _v) const
{
	if (size != _v.size)
	{
		return false;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (v[i] != _v.v[i])
			return false;
	}
	return true;
}

Vector& Vector::operator+=(const Vector& _v)
{
	*this = *this + _v;
	return *this;
}

Vector& Vector::operator-=(const Vector& _v)
{
	*this = *this - _v;
	return *this;
}

Vector& Vector::operator*=(double n)
{
	*this = *this * n;
	return *this;
}

Vector & Vector::operator/=(double n)
{
	*this = *this / n;
	return *this;
}

bool Vector::operator!=(const Vector& _v) const
{
	return !(*this == _v);
}

bool Vector::operator>(const Vector& _v) const
{
	return len() > _v.len();
}

bool Vector::operator>=(const Vector& _v) const
{
	return len() >= _v.len();
}

bool Vector::operator<(const Vector& _v) const
{
	return len() < _v.len();
}

bool Vector::operator<=(const Vector& _v) const
{
	return len() <= _v.len();
}

Vector Vector::operator+()
{
	Vector result(*this);
	return result;
}

Vector Vector::operator-()
{
	Vector result(*this);
	result *= -1;
	return result;
}

double& Vector::operator[](size_t index)
{
	if ((index < size) && (index >= 0))
		return v[index];
	throw std::out_of_range("No element with that index.");
}

const double& Vector::operator[](size_t index) const
{
	if ((index < size) && (index >= 0))
		return v[index];
	throw std::out_of_range("No element with that index.");
}

void* Vector::operator new(size_t _size)
{
	void* ptr = ::new char[_size];
	if (!ptr)
		throw std::bad_alloc();
	return ptr;
}

void* Vector::operator new[](size_t _size, int n)
{
	void* ptr = ::new char[n * _size];
	if (!ptr)
		throw std::bad_alloc();
	return ptr;
}

void Vector::operator delete(void* ptr)
{
	free(ptr);
}

void Vector::operator delete[](void* ptr)
{
	free(ptr);
}

Vector operator*(double m, const Vector& _v)
{
	Vector result(_v);
	size_t size = _v.dim();
	for (size_t i = 0; i < size; i++)
	{
		result[i] *= m;
	}
	return result;
}

const char* VectorDivizionByZero::what() const
{
	return what_str.c_str();
}

const char* VectorUnequalDimensionException::what() const
{
	return what_str.c_str();
}
