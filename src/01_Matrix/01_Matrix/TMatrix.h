#ifndef _TMATRIX_H_
#define _TMATRIX_H_
#include "TVector.h"

template <typename ValueType>
class TMatrix : public TVector<TVector<ValueType>>
{
public:
	explicit TMatrix(size_t size = 10);
	TMatrix(const TMatrix<ValueType>& other);
	TMatrix(const TVector<TVector<ValueType>>& raw);
	~TMatrix() = default;

	ValueType determinant() const;
	void fillRandomly(ValueType valuesFrom = ValueType(0), ValueType valuesTo = ValueType(1));
	void fill(ValueType value = ValueType(0));

	bool operator==(const TMatrix<ValueType>& other) const;
	bool operator!=(const TMatrix<ValueType>& other) const;

	TMatrix<ValueType>& operator=(const TMatrix<ValueType>& other);
	TMatrix<ValueType> operator+(ValueType value);
	TMatrix<ValueType> operator-(ValueType value);
	TMatrix<ValueType> operator*(ValueType value);
	TMatrix<ValueType> operator+(const TMatrix& other);
	TMatrix<ValueType> operator-(const TMatrix& other);
	TMatrix<ValueType> operator*(const TMatrix& other);
	TVector<ValueType> operator*(const TVector<ValueType>& vector);

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
TMatrix<ValueType>::TMatrix(const TVector<TVector<ValueType>>& raw) :
	TVector<TVector<ValueType>>(raw)
{

}

template<typename ValueType>
bool TMatrix<ValueType>::operator==(const TMatrix<ValueType>& other) const
{
	if (this->size != other.size)
		return false;
	for (size_t i = 0; i < this->size; i++)
		if(this->elements[i] != other.elements[i])
			return false;
	return true;
}

template<typename ValueType>
bool TMatrix<ValueType>::operator!=(const TMatrix<ValueType>& other) const
{
	if (this->size != other.size)
		return true;
	for (size_t i = 0; i < this->size; i++)
		if (this->elements[i] != other.elements[i])
			return true;
	return false;
}

template<typename ValueType>
TMatrix<ValueType>& TMatrix<ValueType>::operator=(const TMatrix<ValueType>& other)
{
	if (this == &other)
		return *this;
	if (this->size != other.size)
	{
		delete[] this->elements;
		this->elements = new TVector<ValueType>[other.size];
	}
	this->size = other.size;
	for (size_t i = 0; i < other.size; i++)
		this->elements[i] = other.elements[i];
	return *this;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < this->size; i++)
		this->elements[i] = this->elements[i] + value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < this->size; i++)
		this->elements[i] = this->elements[i] - value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator*(ValueType value)
{
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < this->size; i++)
		this->elements[i] = this->elements[i] * value;
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(const TMatrix& other)
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < this->size; i++)
		this->elements[i] = this->elements[i] + other.elements[i];
	return result;
}

template<typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(const TMatrix& other)
{
	if (this->size != other.size)
		throw MatrixDifferentSizes();
	TMatrix<ValueType> result(*this);
	for (size_t i = 0; i < this->size; i++)
		this->elements[i] = this->elements[i] - other.elements[i];
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
		size_t currentStartIndex = other.elements[i].getStartIndex();
		for (size_t j = currentStartIndex, untilRow = 1; j < result.size; j++, untilRow++)
		{
			result.elements[i][j] = ValueType(0);
			for (size_t k = 0; k < untilRow; k++)
				result.elements[i][j] = result.elements[i][j] + this->elements[i][k + i] * result.elements[k + i][j];
		}
	}
	return result;
}

template<typename ValueType>
TVector<ValueType> TMatrix<ValueType>::operator*(const TVector<ValueType>& vector)
{
	if (this->size != vector.getSize())
		throw VectorInvalidSize();
	TVector<ValueType> result(this->size);
	for (size_t i = 0; i < this->size; i++)
	{
		result[i] = ValueType(0);
		for (size_t j = this->elements[i].getStartIndex(); j < this->size; j++)
			result[i] = result[i] + this->elements[i][j] * vector[j];
	}
	return result;
}

template<typename ValueType>
ValueType TMatrix<ValueType>::determinant() const
{
	ValueType result(0);
	for (size_t i = 0; i < this->size; i++)
		result *= this->elements[i][0];
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