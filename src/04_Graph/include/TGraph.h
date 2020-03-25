#ifndef _TGRAPH_H_
#define _TGRAPH_H_

#include <vector>
#include <queue>

#include "THeap.h"
#include "TDisjointSet.h"
#include "TEdge.h"
#include "TPair.h"
#include "TAdjacencyMatrix.h"
#include "TAdjacencyList.h"
#include "TPathList.h"
#include "Exception.h"

class TGraph
{
    TEdge* edges;
    int vertexCount, edgesCount;
    bool connected(const TAdjacencyMatrix& adjMatrix) const;
    TAdjacencyMatrix generateAdjacencyMatrix() const;
    void freeEdges();
public:
    TGraph();
    TGraph(std::initializer_list<TEdge> edgesList, int vertexCount_);
    void output() const;
    TGraph kruskalAlgorithm() const;
    TPathList dijkstraAlgorithm(TVertexId startVertex = 0) const;

    classException(SelfLoopedGraphError, "Graph has self-loops.");
    classException(DirectedGraphError, "Graph has directed edges.");
    classException(MulticonnectedGraphError, "Graph has more than one connectivity component.");
    classException(InvalidParameterError, "Graph has invalid metrics given.");
};

#endif //!_TGRAPH_H_