#include "TMatrix.h"
#include <ctime>

template<typename ValueType>
ValueType random(ValueType min = ValueType(0), ValueType max = ValueType(1))
{
	return ValueType(rand() % (int)(max - min + ValueType(1))) + min;
}

int main()
{
	srand((unsigned)time(0));
	size_t commonSize   = random<size_t>(2, 6), uncommonSize = random<size_t>(2, 6);
	TVector<double> vectors[]  = { TVector<double>(commonSize), TVector<double>(uncommonSize) };
	TVector <TVector<double>> vectorOfVectors(commonSize);
	TMatrix<double> matrixes[] = { TMatrix<double>(commonSize), TMatrix<double>(commonSize),TMatrix<double>(uncommonSize),  TMatrix<double>(commonSize) };

	enum Idx
	{
		A, B, C, Result
	};

	for (size_t i = 0; i < 2; i++)
		vectors[i].fillRandomly(0., 10.);
	for (size_t i = 0; i < 3; i++)
		matrixes[i].fillRandomly(0., 10.);

	std::cout << "Vector a: " << vectors[Idx::A] << '\n';
	std::cout << "Vector b: " << vectors[Idx::B] << '\n';

	std::cout << "Matrix A: \n" << matrixes[Idx::A] << '\n';
	std::cout << "Matrix B: \n" << matrixes[Idx::B] << '\n';
	std::cout << "Matrix C: \n" << matrixes[Idx::C] << '\n';

	std::cout << "Assignment B to other: \n";
	std::cout << (matrixes[Idx::Result] = matrixes[Idx::B]);
	matrixes[Idx::Result].fill(0.);

	std::cout << "Generating convertible vector...\n";
	for (size_t i = 0; i < commonSize; i++)
	{
		TVector<double> vector(commonSize - i);
		for (size_t j = i; j < commonSize; j++)
			vector[j - i] = random<double>(0., 10.);
		vectorOfVectors[i] = vector;
	}
	std::cout << vectorOfVectors;
	std::cout << "\nAssuming vector of vectors to matrix: \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = vectorOfVectors);
	}
	catch (MatrixNonConvertible& e)
	{
		std::cout << e.what();
	}
	vectorOfVectors[0] = TVector<double>(uncommonSize);
	std::cout << "\nAssuming vector of vectors (with first row length of " << uncommonSize << " instead of "<< commonSize << ") to matrix: \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = vectorOfVectors);
	}
	catch (MatrixNonConvertible& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nEquality (A == B): ";
	if (matrixes[Idx::A] == matrixes[Idx::B])
		std::cout << "true";
	else
		std::cout << "false";

	std::cout << "\nInequality (A != B): ";
	if (matrixes[Idx::A] != matrixes[Idx::B])
		std::cout << "true";
	else
		std::cout << "false";

	std::cout << "\nAddition (A + B): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] + matrixes[Idx::B]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nAddition (A + C): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] + matrixes[Idx::C]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nSubstraction (A - B): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] - matrixes[Idx::B]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nSubstraction (A - C): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] - matrixes[Idx::C]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nMultiplication (A * B): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] * matrixes[Idx::B]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nMultiplication (A * C): \n";
	try
	{
		std::cout << (matrixes[Idx::Result] = matrixes[Idx::A] * matrixes[Idx::C]);
	}
	catch (MatrixDifferentSizes& e)
	{
		std::cout << e.what();
	}

	double operand = random(0., 10.);
	std::cout << "\nAddition (A + " << operand << "): \n" << (matrixes[Idx::A] + operand);
	std::cout << "\nSubstraction (A - " << operand << "): \n" << (matrixes[Idx::A] - operand); 
	std::cout << "\nMultiplication (A * " << operand << "): \n" << (matrixes[Idx::A] * operand);

	std::cout << "\nMultiplication (A * a): \n";
	try
	{
		std::cout << (matrixes[Idx::A] * vectors[Idx::A]);
	}
	catch (VectorInvalidSize& e)
	{
		std::cout << e.what();
	}
	std::cout << "\nMultiplication (A * b): \n";
	try
	{
		std::cout << (matrixes[Idx::A] * vectors[Idx::B]);
	}
	catch (VectorInvalidSize& e)
	{
		std::cout << e.what();
	}

	std::cout << "\nDeterminant of A: " << matrixes[Idx::A].determinant();
	std::cout << '\n';
	
}