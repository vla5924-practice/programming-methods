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
	TVector(size_t size = 10, size_t startIndex = 0);
	TVector(const TVector& other);
	~TVector();

	bool operator==(const TVector& other) const;
	bool operator!=(const TVector& other) const;

	TVector& operator=(const TVector& other);
	TVector operator+(ValueType value);
	TVector operator-(ValueType value);
	TVector operator*(ValueType value);
	TVector operator+(const TVector& other);
	TVector operator-(const TVector& other);
	ValueType operator*(const TVector& other);

	size_t dim() const;
	ValueType length() const;

	friend std::ostream& operator<<(std::ostream& outputStream, const TVector& vector);
	friend std::istream& operator>>(std::istream& inputStream, TVector& vector);
	ValueType& operator[](size_t index);
};

template<typename ValueType>
TVector<ValueType>::TVector(size_t size, size_t startIndex) : size(size), startIndex(startIndex)
{
	elements = size ? new ValueType[size] : nullptr;
}

template<typename ValueType>
TVector<ValueType>::TVector(const TVector& other) : size(other.size), startIndex(other.startIndex)
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
bool TVector<ValueType>::operator==(const TVector& other) const
{
	if (size != other.size)
		return false;
	for (size_t i = 0; i < size; i++)
		if (elements[i] != other.elements[i])
			return false;
	return true;
}

template<typename ValueType>
bool TVector<ValueType>::operator!=(const TVector& other) const
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
	if (size > 0)
		delete[] elements;
	size = other.size;
	startIndex = other.startIndex;
	elements = new ValueType[size];
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
TVector<ValueType> TVector<ValueType>::operator+(const TVector& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] += other.elements[i];
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const TVector& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] -= other.elements[i];
	return result;
}

template<typename ValueType>
ValueType TVector<ValueType>::operator*(const TVector& other)
{
	if (size != other.size)
		throw VecDifferentSizes();
	ValueType result;
	for (size_t i = 0; i < size; i++)
		result += elements[i] * other.elements[i];
	return result;
}

template<typename ValueType>
size_t TVector<ValueType>::dim() const
{
	return size;
}

template<typename ValueType>
ValueType TVector<ValueType>::length() const
{
	ValueType result;
	for (size_t i = 0; i < size; i++)
		result += elements[i] * elements[i];
	return sqrt(result);
}

template<typename ValueType>
ValueType& TVector<ValueType>::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range("olala");
	return elements[index];
}

template<typename ValueType>
std::ostream& operator<<(std::ostream& outputStream, const TVector<ValueType>& vector)
{
	if (vector.size == 0)
		return outputStream;
	for (size_t i = 0; i < vector.size - 1; i++)
		outputStream << vector.elements[i] << ' ';
	return outputStream << vector.elements[vector.size - 1];
}

template<typename ValueType>
std::istream& operator>>(std::istream& inputStream, TVector<ValueType>& vector)
{
	if (vector.size == 0)
		return inputStream;
	for (size_t i = 0; i < vector.size; i++)
		inputStream >> vector.elements[i];
	return inputStream;
}

#endif // !_TVECTOR_H_