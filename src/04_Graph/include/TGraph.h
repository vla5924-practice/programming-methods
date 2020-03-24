#ifndef _TGRAPH_H_
#define _TGRAPH_H_
#include "TEdge.h"
#include "THeap.h"
#include "TDisjointSet.h"

struct TGraph
{
    TEdge* edges = nullptr;
    int vertexCount = 0, edgesCount = 0;

    TGraph() = default;
    TGraph(std::initializer_list<TEdge> data);
    void output() const;
    TGraph kruskalAlgorithm() const;
    void dijkstraAlgorithm(int*& dist, int*& up) const;
};

#endif //!_TGRAPH_H_