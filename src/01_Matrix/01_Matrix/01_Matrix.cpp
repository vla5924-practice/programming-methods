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
	size_t commonSize = random<size_t>(3, 6);
	size_t uncommonSize = random<size_t>(0, 1) ? commonSize + random<size_t>(1, 2) : commonSize - random<size_t>(1, 2);
	TVector<double> vectors[] =  { TVector<double>(commonSize), TVector<double>(uncommonSize) };
	TMatrix<double> matrixes[] = { TMatrix<double>(commonSize), TMatrix<double>(commonSize), TMatrix<double>(uncommonSize),  TMatrix<double>(commonSize) };

//	TVector<double> vectors[] =  { TVector<double>(3), TVector<double>(2) };
//	TMatrix<double> matrixe(5);
//	TMatrix<double> matrixes[] = { TMatrix<double>(5), TMatrix<double>(3), TMatrix<double>(2),  TMatrix<double>(3) };

	enum Idx
	{
		A, B, C, Result
	};

	for (size_t i = 0; i < 2; i++)
		vectors[i].fillRandomly(0., 10.);
	for (size_t i = 0; i < 3; i++)
		matrixes[i].fillRandomly(0., 10.);
	//matrixes[Idx::Result].fill(0.);

	std::cout << "Vector a: " << vectors[Idx::A] << '\n';
	std::cout << "Vector b: " << vectors[Idx::B] << '\n';

	std::cout << "Matrix A: \n" << matrixes[Idx::A] << '\n';
	std::cout << "Matrix B: \n" << matrixes[Idx::B] << '\n';
	std::cout << "Matrix C: \n" << matrixes[Idx::C] << '\n';

	std::cout << "Assignment B to other: \n";
	std::cout << (matrixes[Idx::Result] = matrixes[Idx::B]);
	matrixes[Idx::Result].fill(0.);

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