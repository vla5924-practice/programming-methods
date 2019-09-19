#ifndef _TMATRIX_H_
#define _TMATRIX_H_
#include "TVector.h"

template <typename ValueType>
class TMatrix : public TVector<TVector<ValueType>>
{
public:
	TMatrix(size_t size = 10);
	TMatrix(const TMatrix& other);
	TMatrix(const TVector<TVector<ValueType> >& raw);
	~TMatrix();

	bool operator==(const TMatrix& other) const;
	bool operator!=(const TMatrix& other) const;

	TMatrix& operator=(const TMatrix& other);
	TMatrix operator+(ValueType value);
	TMatrix operator-(ValueType value);
	TMatrix operator*(ValueType value);
	TMatrix operator+(const TMatrix& other);
	TMatrix operator-(const TMatrix& other);
	ValueType operator*(const TMatrix& other);
	TVector<ValueType> operator*(const TVector<ValueType>& vector);

	ValueType determinant() const;

	friend std::ostream& operator<<(std::ostream& outputStream, const TMatrix& matrix);
	friend std::istream& operator>>(std::istream& inputStream, TMatrix& matrix);
};


template<typename ValueType>
TMatrix<ValueType>::TMatrix(size_t size) : TVector<TVector<ValueType>>(size)
{
	//for (size_t i = size; i >= 1; i--)
	//	this->elements[i] = TVector<ValueType>(i);
}

template<typename ValueType>
TMatrix<ValueType>::TMatrix(const TMatrix& other) : TVector<TVector<ValueType>>(other)
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
ValueType TMatrix<ValueType>::determinant() const
{
	ValueType result;
	for (size_t i = 0; i < this->size; i++)
		result *= this->elements[i][0];
	return result;
}

template<typename ValueType>
std::ostream& operator<<(std::ostream& outputStream, const TMatrix<ValueType>& matrix)
{
	if (matrix.size == 0)
		return outputStream;
	for (size_t i = 0; i < matrix.size - 1; i++)
		outputStream << matrix.elements[i] << '\n';
	return outputStream << matrix.elements[matrix.size - 1];
}

template<typename ValueType>
std::istream& operator>>(std::istream& inputStream, TMatrix<ValueType>& matrix)
{
	if (matrix.size == 0)
		return inputStream;
	for (size_t i = 0; i < matrix.size - 1; i++)
		inputStream >> matrix.elements[i] << '\n';
	return inputStream;
}

#endif // !_TMATRIX_H_