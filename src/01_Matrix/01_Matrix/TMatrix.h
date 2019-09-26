#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include "TVector.h"

template<typename ValueType>
class TMatrix : public TVector<TVector<ValueType>>
{
public:
	explicit TMatrix(size_t size = 10);
	TMatrix(const TMatrix& other);
	TMatrix(const TVector<TVector<ValueType>>& vector);
	~TMatrix() = default;

	bool operator==(const TMatrix& other) const;
	bool operator!=(const TMatrix& other) const;

	TMatrix& operator=(const TMatrix& other);
	TMatrix operator+(ValueType value);
	TMatrix operator-(ValueType value);
	TMatrix operator*(ValueType value);
	TMatrix operator+(const TMatrix& other);
	TMatrix operator-(const TMatrix& other);
	TMatrix operator*(const TMatrix& other);
	TVector<ValueType> operator*(const TVector<ValueType>& other);

	ValueType determinant();
	void fillRandomly(ValueType valuesFrom = ValueType(0), ValueType valuesTo = ValueType(1));
	void fill(ValueType value = ValueType(0));

	friend std::ostream& operator<<(std::ostream& outputStream, const TMatrix<ValueType>& matrix)
	{
		if (matrix.size == 0)
			return outputStream;
		for (size_t i = 0; i < matrix.size - 1; i++)
			outputStream << matrix.elements[i] << '\n';
		return outputStream << matrix.elements[matrix.size - 1];
	}
	friend std::istream& operator>>(std::istream& inputStream, TMatrix<ValueType>& matrix)
	{
		if (matrix.size == 0)
			return inputStream;
		for (size_t i = 0; i < matrix.size - 1; i++)
			inputStream >> matrix.elements[i];
		return inputStream;
	}
};

template<typename ValueType>
TMatrix<ValueType>::TMatrix(size_t size) : TVector<TVector<ValueType>>(size)
{
	if (size == 0)
		throw MatrixInvalidSize();
	for (size_t i = 0; i < size; i++)
		this->elements[i] = TVector<ValueType>(size - i, i);
}

template<typename ValueType>
TMatrix<ValueType>::TMatrix(const TMatrix<ValueType>& other)
{
	this->size = other.size;
	this->elements = new TVector<ValueType>[other.size];
	for (size_t i = 0; i < other.size; i++)
		this->elements[i] = other.elements[i];
}

template<typename ValueType>
TMatrix<ValueType>::TMatrix(const TVector<TVector<ValueType>>& vector) : TVector<TVector<ValueType>>(vector.size)
{
	bool isConvertible = true, isTrulyTriangle = false;
	for (size_t i = 0; i < this->size; i++)
		if (vector[i].getSize() != this->size)
		{
			isConvertible &= false;
			break;
		}
	if (!isConvertible)
	{
		isConvertible = true;
		for (size_t i = 0; i < this->size; i++)
			if (vector[i].getSize() != this->size - i)
			{
				isConvertible &= false;
				break;
			}
		isTrulyTriangle = true;
	}
	if (!isConvertible)
		throw MatrixNonConvertible();
	if (isTrulyTriangle)
		for (size_t i = 0; i < this->size; i++)
			this->elements[i] = vector.elements[i];
	else
		for (size_t i = 0; i < this->size; i++)
			for(size_t j = 0; j < this->size - i; j++)
				this->elements[i][j] = vector.elements[i][j + i];
}

template<typename ValueType>
bool TMatrix<ValueType>::operator==(const TMatrix<ValueType>& other) const
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	for (size_t i = 0; i < other.size; i++)
		if (this->elements[i] != other.elements[i])
			return false;
	return true;
}

template<typename ValueType>
bool TMatrix<ValueType>::operator!=(const TMatrix<ValueType>& other) const
{
	return !(*this == other);
}

template<typename ValueType>
TMatrix<ValueType>& TMatrix<ValueType>::operator=(const TMatrix<ValueType>& other)
{
	if (this != &other)
	{
		if (this->size != other.size)
		{
			this->size = other.size;
			delete[] this->elements;
			this->elements = new TVector<ValueType>[other.size];
		}
		for (size_t i = 0; i < other.size; i++)
			this->elements[i] = other.elements[i];
	}
	return *this;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] = this->elements[i] + value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] = result.elements[i] - value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator*(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] = result.elements[i] * value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(const TMatrix& other)
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] = result.elements[i] + other.elements[i];
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(const TMatrix& other)
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
		result.elements[i] = result.elements[i] - other.elements[i];
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator*(const TMatrix& other)
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < result.size; i++)
	{
		size_t untilRow = 1;
		size_t currentStartIndex = other.elements[i].getStartIndex();
		for (size_t j = currentStartIndex; j < result.size; j++)
		{
			result.elements[i][j] = ValueType(0);
			for (size_t k = 0; k < untilRow; k++)
				result.elements[i][j] = result.elements[i][j] + this->elements[i][k + i] * other.elements[k + i][j];
			untilRow++;
		}
	}
	return result;
}

template<typename ValueType>
TVector<ValueType> TMatrix<ValueType>::operator*(const TVector<ValueType>& other)
{
	size_t size = other.getSize();
	if (this->size != size)
		throw VectorInvalidSize();
	TVector<ValueType> result(size);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = ValueType(0);
		size_t currentStartIndex = this->elements[i].getStartIndex();
		for (size_t j = currentStartIndex; j < size; j++)
			result[i] = result[i] + this->elements[i][j] * other[j];
	}
	return result;
}

template<typename ValueType>
ValueType TMatrix<ValueType>::determinant()
{
	ValueType result(1);
	for (size_t i = 0; i < this->size; i++)
		result = result * this->elements[i][i];
	return result;
}

template<typename ValueType>
void TMatrix<ValueType>::fillRandomly(ValueType valuesFrom, ValueType valuesTo)
{
	if (this->size == 0)
		return;
	for (size_t i = 0; i < this->size; i++)
		this->elements[i].fillRandomly(valuesFrom, valuesTo);
}

template<typename ValueType>
void TMatrix<ValueType>::fill(ValueType value)
{
	if (this->size == 0)
		return;
	for (size_t i = 0; i < this->size; i++)
		this->elements[i].fill(value);
}

#endif // !_TMATRIX_H_