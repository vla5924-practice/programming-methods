#ifndef _TVECTOR_H_
#define _TVECTOR_H_
#include <iostream>
#include <cstring>
#include <cmath>
#include "Exceptions.h"

template <typename ValueType>
class TVector
{
protected:
	size_t size;
	ValueType* elements;
	size_t startIndex;
public:
	explicit TVector(size_t size = 10, size_t startIndex = 0);
	TVector(const TVector<ValueType>& other);
	~TVector();

	bool operator==(const TVector<ValueType>& other) const;
	bool operator!=(const TVector<ValueType>& other) const;

	TVector<ValueType>& operator=(const TVector<ValueType>& other);
	TVector<ValueType> operator+(ValueType value);
	TVector<ValueType> operator-(ValueType value);
	TVector<ValueType> operator*(ValueType value);
	TVector<ValueType> operator+(const TVector<ValueType>& other);
	TVector<ValueType> operator-(const TVector<ValueType>& other);
	ValueType operator*(const TVector<ValueType>& other);

	size_t getStartIndex() const;
	size_t getSize() const;
	double length() const;

	friend std::ostream& operator<<(std::ostream& outputStream, const TVector& vector)
	{
		if (vector.size == 0)
			return outputStream;
		for (size_t i = 0; i < vector.size - 1; i++)
			outputStream << vector.elements[i] << ' ';
		return outputStream << vector.elements[vector.size - 1];
	}
	friend std::istream& operator>>(std::istream& inputStream, TVector& vector)
	{
		if (vector.size == 0)
			return inputStream;
		for (size_t i = 0; i < vector.size; i++)
			inputStream >> vector.elements[i];
		return inputStream;
	}
	ValueType& operator[](size_t index);
	const ValueType& operator[](size_t index) const;
};

template<typename ValueType>
TVector<ValueType>::TVector(size_t size, size_t startIndex) : size(size), startIndex(startIndex)
{
	elements = size ? new ValueType[size] : nullptr;
}

template<typename ValueType>
TVector<ValueType>::TVector(const TVector<ValueType>& other) : size(other.size), startIndex(other.startIndex)
{
	elements = new ValueType[size];
	memcpy(elements, other.elements, size * sizeof(ValueType));
}

template<typename ValueType>
TVector<ValueType>::~TVector()
{
	if (size > 0)
		delete[] elements;
}

template<typename ValueType>
bool TVector<ValueType>::operator==(const TVector<ValueType>& other) const
{
	if (size != other.size)
		return false;
	for (size_t i = 0; i < size; i++)
		if (elements[i] != other.elements[i])
			return false;
	return true;
}

template<typename ValueType>
bool TVector<ValueType>::operator!=(const TVector<ValueType>& other) const
{
	if (size != other.size)
		return true;
	for (size_t i = 0; i < size; i++)
		if (elements[i] != other.elements[i])
			return true;
	return false;
}

template<typename ValueType>
TVector<ValueType>& TVector<ValueType>::operator=(const TVector& other)
{
	if (this == &other)
		return *this;
	if (size != other.size)
	{
		delete[] elements;
		elements = new ValueType[size];
		size = other.size;
	}
	startIndex = other.startIndex;
	memcpy(elements, other.elements, size * sizeof(ValueType));
	return *this;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] += value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] -= value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator*(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] *= value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(const TVector<ValueType>& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] += other.elements[i];
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const TVector<ValueType>& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] -= other.elements[i];
	return result;
}

template<typename ValueType>
ValueType TVector<ValueType>::operator*(const TVector<ValueType>& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	ValueType result;
	for (size_t i = 0; i < size; i++)
		result += elements[i] * other.elements[i];
	return result;
}

template<typename ValueType>
size_t TVector<ValueType>::getStartIndex() const
{
	return startIndex;
}

template<typename ValueType>
size_t TVector<ValueType>::getSize() const
{
	return size;
}

template<typename ValueType>
double TVector<ValueType>::length() const
{
	ValueType result;
	for (size_t i = 0; i < size; i++)
		result += elements[i] * elements[i];
	return sqrt(result);
}

template<typename ValueType>
const ValueType& TVector<ValueType>::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("olala");
	return elements[index];
}

template<typename ValueType>
ValueType& TVector<ValueType>::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range("olala");
	return elements[index];
}

#endif // !_TVECTOR_H_