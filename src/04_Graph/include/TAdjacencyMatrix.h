#ifndef _TADJACENCYMATRIX_H_
#define _TADJACENCYMATRIX_H_

#include <iostream>

class TAdjacencyMatrix
{
    bool* matrix;
    int vertexCount;
public:
    TAdjacencyMatrix();
    TAdjacencyMatrix(const TAdjacencyMatrix& other);
    TAdjacencyMatrix(TAdjacencyMatrix&& other);
    explicit TAdjacencyMatrix(int vertexCount_);
    ~TAdjacencyMatrix();

    bool* operator[](int i) { return matrix + i * vertexCount; }
    const bool* operator[](int i) const { return matrix + i * vertexCount; }
    inline int size() const;
};

#endif