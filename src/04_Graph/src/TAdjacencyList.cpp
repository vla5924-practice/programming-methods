#include "TAdjacencyList.h"

const std::vector<TVertexId>& TAdjacencyList::operator[](TVertexId i) const
{
    return list[i];
}

void TAdjacencyList::add(TVertexId listOnVertex, TVertexId addingVertex)
{
    list[listOnVertex].push_back(addingVertex);
}
