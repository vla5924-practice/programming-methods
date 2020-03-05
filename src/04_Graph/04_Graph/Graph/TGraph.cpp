#include "TGraph.h"

TGraph TGraph::kruskalAlgorithm() const
{
    TSplitSet vertex(vertexCount);
    TGraph result;
    result.vertexCount = vertexCount;
    result.edges = new TEdge[vertexCount - 1];
    for (int i = 0; i < vertexCount; i++)
    {
        vertex.createSingleton(i);
    }
    THeap<TEdge> heapEdges(edges, edgesCount, 2);
    int tEdgesCount = 0;
    while ((tEdgesCount != vertexCount - 1) && (!heapEdges.empty()))
    {
        TEdge edge = heapEdges.popMin();
        int setX = vertex.findSet(edge.x), setY = vertex.findSet(edge.y);
        if (setX != setY)
        {
            vertex.unite(setX, setY);
            result.edges[tEdgesCount] = edge;
            tEdgesCount++;
        }
    }
    result.edgesCount = tEdgesCount;
    return result;
}

TGraph TGraph::dijkstraAlgorithm() const
{
    return TGraph();
}

void TGraph::output() const
{
    for (int i = 0; i < edgesCount; i++)
        std::cout << '(' << edges[i].x << ", " << edges[i].y << ") " << edges[i].weight << '\n';
}