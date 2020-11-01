#include "TAdjacencyMatrix.h"

TAdjacencyMatrix::TAdjacencyMatrix()
{
    matrix = nullptr;
    vertexCount = 0;
}

TAdjacencyMatrix::TAdjacencyMatrix(const TAdjacencyMatrix& other)
{
    vertexCount = other.vertexCount;
    int memSize = size();
    matrix = new bool[memSize];
    for (int i = 0; i < memSize; i++)
        matrix[i] = other.matrix[i];
}

TAdjacencyMatrix::TAdjacencyMatrix(TAdjacencyMatrix&& other)
{
    vertexCount = other.vertexCount;
    matrix = other.matrix;
    other.vertexCount = 0;
    other.matrix = nullptr;
}

TAdjacencyMatrix::TAdjacencyMatrix(int vertexCount_)
{
    vertexCount = vertexCount_;
    int memSize = size();
    matrix = new bool[memSize];
    for (int i = 0; i < memSize; i++)
        matrix[i] = false;
}

TAdjacencyMatrix::~TAdjacencyMatrix()
{
    if (matrix)
        delete[] matrix;
}

inline int TAdjacencyMatrix::size() const
{
    return vertexCount * vertexCount;
}

void TAdjacencyMatrix::print() const
{
    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
            std::cout << (*this)[i][j] << ' ';
        std::cout << '\n';
    }
}
