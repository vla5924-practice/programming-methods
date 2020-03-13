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

void TGraph::dijkstraAlgorithm(int*& dist, int*& up, int vertexStart) const
{
    dist = new int(vertexCount);
    up = new int(vertexCount);
    for (int i = 0; i < vertexCount; i++)
    {
        if (i == vertexStart)
            dist[i] = 0;
        else
            dist[i] = INT_MAX;
        up[i] = 0;
    }
    int k = 0;
    THeap<int> marks(dist, vertexCount, 2);
    while (!marks.empty())
    {
        int minMark = marks.topMin(), minMarkVertex;
        for (int i = 0; i < vertexCount; i++)
            if (dist[i] == minMark)
                minMarkVertex = i;
        for (int i = 0; i < edgesCount; i++)
        {
            if (edges[i].incidental(minMarkVertex))
            {
                if (dist[minMarkVertex] + edges[i].weight < dist[edges[i].x])
                {
                    dist[edges[i].x] = dist[minMarkVertex] + edges[i].weight;
                    up[edges[i].x] = minMarkVertex;
                }
                if (dist[minMarkVertex] + edges[i].weight < dist[edges[i].y])
                {
                    dist[edges[i].y] = dist[minMarkVertex] + edges[i].weight;
                    up[edges[i].y] = minMarkVertex;
                }
            }
        }
        marks.output();                                                // DEBUG
        marks.popMin();
        marks.output();                                                // DEBUG
        for (int i = 0; i < vertexCount; i++)                          // DEBUG
            std::cout << up[i] << "|";                                 // DEBUG
        std::cout << std::endl << "-------------------" << std::endl;  // DEBUG
    }
}

TGraph::TGraph(std::initializer_list<TEdge> data)
{
    edgesCount = static_cast<int>(data.size());
    edges = new TEdge[edgesCount];
    int i = 0;
    for (TEdge edge : data)
    {
        edges[i++] = edge;
    }
}

void TGraph::output() const
{
    for (int i = 0; i < edgesCount; i++)
        std::cout << '(' << edges[i].x << ", " << edges[i].y << ") {" << edges[i].weight << "}\n";
}