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
	~TMatrix();

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

	ValueType determinant() const;
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
			inputStream >> matrix.elements[i] << '\n';
		return inputStream;
	}
};


template<typename ValueType>
TMatrix<ValueType>::TMatrix(size_t size) : TVector<TVector<ValueType>>(size)
{
	// assert{size == 0}
	for (size_t i = 0; i < size; i++)
		this->elements[i] = TVector<ValueType>(size - i, i);
}

template<typename ValueType>
TMatrix<ValueType>::TMatrix(const TMatrix<ValueType>& other) : TVector<TVector<ValueType>>(other)
{

}

template<typename ValueType>
TMatrix<ValueType>::TMatrix(const TVector<TVector<ValueType>>& raw) :
	TVector<TVector<ValueType>>(raw)
{

}

template<typename ValueType>
TMatrix<ValueType>::~TMatrix()
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
	this->size = other.size;
	if (this->size != other.size)
	{
		delete[] this->elements;
		this->elements = new TVector<TVector<ValueType>>[other.size];
	}
	for (size_t i = 0; i < other.size; i++)
		this->elements[i] = other.elements[i];
	return *this;
}

template<typename ValueType>
ValueType TMatrix<ValueType>::determinant() const
{
	ValueType result;
	for (size_t i = 0; i < this->size; i++)
		result *= this->elements[i][0];
	return result;
}

#endif // !_TMATRIX_H_