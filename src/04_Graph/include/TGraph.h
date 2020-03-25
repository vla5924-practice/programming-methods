#ifndef _TGRAPH_H_
#define _TGRAPH_H_

#include <iostream>
#include <vector>
#include <queue>

#include "THeap.h"
#include "TDisjointSet.h"
#include "TEdge.h"
#include "TPair.h"
#include "TAdjacencyMatrix.h"
#include "TAdjacencyList.h"
#include "TPathData.h"
#include "Exception.h"

using TEdgeFilterFunc = bool (*) (const TEdge&);
using TEdgeList = std::vector<TEdge>;

class TGraph
{
    TEdge* edges;
    int vertexCount, edgesCount;
    bool connected(const TAdjacencyMatrix& adjMatrix) const;
    void freeEdges();
public:
    TGraph();
    TGraph(const TGraph& other);
    TGraph(TGraph&& other);
    TGraph(std::initializer_list<TEdge> edgesList, int vertexCount_);
    TGraph(TEdge* edges_, int edgesCount_, int vertexCount_);
    ~TGraph();

    TGraph& operator=(const TGraph& other);
    TGraph& operator=(TGraph&& other);

    void print() const;
    TAdjacencyMatrix generateAdjacencyMatrix() const;
    TGraph kruskalAlgorithm() const;
    TPathData dijkstraAlgorithm(TVertexId startVertex = 0) const;

    inline int getVertexCount() const;
    inline int getEdgesCount() const;
    bool hasEdge(TVertexId x, TVertexId y) const;
    TEdgeList getEdges() const;
    TEdgeList getEdges(TEdgeFilterFunc filter) const;
    float getWeight() const;
    float getWeight(TEdgeFilterFunc filter) const;

    friend std::istream& operator>>(std::istream& input, TGraph& graph);

    classException(SelfLoopedGraphError, "Graph has self-loops.");
    classException(DirectedGraphError, "Graph has directed edges.");
    classException(MulticonnectedGraphError, "Graph has more than one connectivity component.");
    classException(InvalidParameterError, "Graph has invalid metrics given.");
};

#endif