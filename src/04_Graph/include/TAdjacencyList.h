#ifndef _TADJACENCYLIST_H_
#define _TADJECENCYLIST_H_
#include <vector>
#include "TEdge.h"

class TAdjacencyList
{
    std::vector<std::vector<TVertexId>> list;
public:
    TAdjacencyList() = default;
    explicit TAdjacencyList(int vertexCount = 0) : list(vertexCount) {};
    TAdjacencyList(const TAdjacencyList&) = default;
    TAdjacencyList(TAdjacencyList&&) = default;
    ~TAdjacencyList() = default;

    const std::vector<TVertexId>& operator[](TVertexId i) const;
    void add(TVertexId listOnVertex, TVertexId addingVertex);
};

#endif