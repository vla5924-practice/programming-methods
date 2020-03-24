#include "TGraph.h"

TGraph TGraph::kruskalAlgorithm() const
{
    TDisjointSet vertex(vertexCount);
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

void TGraph::dijkstraAlgorithm(int*& dist, int*& up) const
{
    dist = new int[vertexCount];
    up = new int[vertexCount];
    dist[0] = 0;
    up[0] = 0;
    for (int i = 0; i < vertexCount; i++)
    {
        dist[i] = INT_MAX;
        up[i] = 0;
    }
    THeap<int> marks(dist, vertexCount);
    while (!marks.empty())
    {
        int minMark = marks.popMin(), vertex;
        for (int i = 0; i < vertexCount; i++)
            if (dist[i] == minMark)
                vertex = i;
        for (int i = 0; i < edgesCount; i++)
        {
            if (edges[i].incidental(minMark))
            {
                if (dist[minMark] + edges[i].weight < dist[edges[i].x])
                {
                    dist[edges[i].x] = dist[minMark] + edges[i].weight;
                    up[edges[i].x] = minMark;
                }
                if (dist[minMark] + edges[i].weight < dist[edges[i].y])
                {
                    dist[edges[i].y] = dist[minMark] + edges[i].weight;
                    up[edges[i].y] = minMark;
                }
            }
        }
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