#include "KruskalAlgorithm.h"

TGraph GraphAlgorithms::kruskalAlgorithm(const TGraph& graph)
{
    int resultVertexCount = graph.getVertexCount();
    int resultEdgesCount = resultVertexCount - 1;
    TDisjointSet vertex(resultVertexCount);
    TEdge* resultEdges = new TEdge[resultEdgesCount];
    for (int i = 0; i < resultVertexCount; i++)
        vertex.createSingleton(i);
    THeap<TEdge> heapEdges(resultEdges, resultEdgesCount);
    int tEdgesCount = 0;
    while ((tEdgesCount != resultEdgesCount) && (!heapEdges.empty()))
    {
        TEdge edge = heapEdges.topMin();
        heapEdges.popMin();
        int setX = vertex.findSet(edge.x), setY = vertex.findSet(edge.y);
        if (setX != setY)
        {
            vertex.unite(setX, setY);
            resultEdges[tEdgesCount] = edge;
            tEdgesCount++;
        }
    }
    resultEdgesCount = tEdgesCount;
    return TGraph(resultEdges, resultEdgesCount, resultVertexCount);
}
