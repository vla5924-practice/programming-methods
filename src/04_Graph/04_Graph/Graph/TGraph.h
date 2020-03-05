#ifndef _TGRAPH_H_
#define _TGRAPH_H_
#include "TEdge.h"
#include "../Lib/THeap.h"
#include "../Lib/TSplitSet.h"

struct TGraph
{
    TEdge* edges = nullptr;
    int vertexCount = 0, edgesCount = 0;

    void output() const;
    TGraph kruskalAlgorithm() const;
    TGraph dijkstraAlgorithm() const;
};

#endif //!_TGRAPH_H_