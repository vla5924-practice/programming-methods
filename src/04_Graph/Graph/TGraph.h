#ifndef _TGRAPH_H_
#define _TGRAPH_H_
#include "TEdge.h"
#include "../Lib/THeap.h"
#include "../Lib/TSplitSet.h"

struct TGraph
{
    TEdge* edges = nullptr;
    int vertexCount = 0, edgesCount = 0;
    
    TGraph() = default;
    TGraph(std::initializer_list<TEdge> data);
    void output() const;
    TGraph kruskalAlgorithm() const;
    void dijkstraAlgorithm(int*& dist, int*& up, int vertexStart = 0) const;
};

#endif //!_TGRAPH_H_