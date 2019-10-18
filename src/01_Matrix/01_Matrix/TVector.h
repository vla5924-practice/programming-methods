#ifndef _TVECTOR_H_
#define _TVECTOR_H_

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include "Exceptions.h"

template<typename ValueType>
class TVector
{
protected:
	size_t size;
	size_t startIndex;
	ValueType* elements;

public:
	explicit TVector(size_t _size = 1, size_t _startIndex = 0);
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
	ValueType length() const;

	size_t getSize() const;
	size_t getStartIndex() const;
	//ValueType& at(size_t index);
	//const ValueType& at(size_t index) const;

	ValueType& operator[](size_t index);
	const ValueType& operator[](size_t index) const;

	void fillRandomly(ValueType valuesFrom = ValueType(0), ValueType valuesTo = ValueType(1));
	void fill(ValueType value = ValueType(0));

	friend std::ostream& operator<<(std::ostream& outputStream, const TVector& vector)
	{
		outputStream << "[ ";
		if (vector.size == 0)
			return outputStream << ']';
		for (size_t i = 0; i < vector.startIndex; i++)
			outputStream << std::setw(5) << std::setprecision(2) << std::right << ValueType(0) << ' ';
		for (size_t i = 0; i < vector.size; i++)
			outputStream << std::setw(5) << std::setprecision(2) << std::right << vector.elements[i] << ' ';
		return outputStream << ']';
	}
	friend std::istream& operator>>(std::istream& inputStream, TVector& vector)
	{
		if (vector.size == 0)
			return inputStream;
		for (size_t i = 0; i < vector.size; i++)
			inputStream >> vector.elements[i];
		return inputStream;
	}
};

template<typename ValueType>
TVector<ValueType>::TVector(size_t size, size_t startIndex) : size(size), startIndex(startIndex)
{
	if (size == 0)
		throw VectorInvalidSize();
	elements = new ValueType[size];
}

template<typename ValueType>
TVector<ValueType>::TVector(const TVector& other)
{
	size = other.size;
	elements = new ValueType[size];
	for (size_t i = 0; i < size; i++)
		elements[i] = other.elements[i];
	startIndex = other.startIndex;
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
	if ((size != other.size) || (startIndex != other.startIndex))
		return false;
	for (size_t i = 0; i < size; i++)
		if (elements[i] != other.elements[i])
			return false;
	return true;
}

template<typename ValueType>
bool TVector<ValueType>::operator!=(const TVector& other) const
{
	return !(*this == other);
}

template<typename ValueType>
TVector<ValueType>& TVector<ValueType>::operator=(const TVector& other)
{
	if (*this != other)
	{
		if (size != other.size)
		{
			size = other.size;
			delete[] elements;
			elements = new ValueType[size];
		}
		startIndex = other.startIndex;
		for (size_t i = 0; i < size; i++)
			elements[i] = other.elements[i];
	}
	return *this;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] += value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] -= value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator*(ValueType value)
{
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] *= value;
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(const TVector& other)
{
	if (size != other.size)
		throw VectorDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] += other.elements[i];
	return result;
}

template<typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const TVector& other)
{
	if (size != other.size)
		throw VectorDifferentSizes();
	TVector<ValueType> result(*this);
	for (size_t i = 0; i < size; i++)
		result.elements[i] -= other.elements[i];
	return result;
}

template<typename ValueType>
ValueType TVector<ValueType>::operator*(const TVector& other)
{
	if (size != other.size)
		throw VectorDifferentSizes();
	ValueType result(0);
	for (size_t i = 0; i < size; i++)
		result += elements[i] * other.elements[i];
	return result;
}

template<typename ValueType>
ValueType TVector<ValueType>::length() const
{
	ValueType result(0);
	for (size_t i = 0; i < size; i++)
		result += elements[i] * elements[i];
	return sqrtf(result);
}

template<typename ValueType>
size_t TVector<ValueType>::getSize() const
{
	return size;
}

template<typename ValueType>
size_t TVector<ValueType>::getStartIndex() const
{
	return startIndex;
}

template<typename ValueType>
ValueType& TVector<ValueType>::operator[](size_t index)
{
	if (index - startIndex >= size)
		throw VectorInvalidIndex();
	return elements[index - startIndex];
}

template<typename ValueType>
const ValueType& TVector<ValueType>::operator[](size_t index) const
{
	if (index - startIndex >= size)
		throw VectorInvalidIndex();
	return elements[index - startIndex];
}

/*template<typename ValueType>
ValueType& TVector<ValueType>::at(size_t index)
{
	if (index >= size)
		throw VectorInvalidIndex();
	return elements[index];
}*/

/*template<typename ValueType>
const ValueType& TVector<ValueType>::at(size_t index) const
{
	if (index >= size)
		throw VectorInvalidIndex();
	return elements[index];
}*/

template<typename ValueType>
void TVector<ValueType>::fillRandomly(ValueType valuesFrom, ValueType valuesTo)
{
	if (size == 0)
		return;
	for (size_t i = 0; i < size; i++)
	{
		ValueType randValue(rand());
		ValueType randOperand = randValue * (valuesTo - valuesFrom) / ValueType(RAND_MAX);
		elements[i] = randOperand + valuesFrom;
	}
}

template<typename ValueType>
void TVector<ValueType>::fill(ValueType value)
{
	if (size == 0)
		return;
	for (size_t i = 0; i < size; i++)
		elements[i] = value;
}

#endif // !_TVECTOR_H_
