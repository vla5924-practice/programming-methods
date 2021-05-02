#include "DijkstraAlgorithm.h"

TPathData GraphAlgorithms::dijkstraAlgorithm(const TGraph& graph, TVertexId startVertex)
{
    int vertexCount = graph.getVertexCount();
    int edgesCount = graph.getEdgesCount();
    TEdge* edges = graph.pEdges();
    float* dist = new float[vertexCount];
    TVertexId* up = new TVertexId[vertexCount];
    TPair* distId = new TPair[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        distId[i].distance = std::numeric_limits<float>::infinity();
        distId[i].vertex = i;
        up[i] = 0;
    }
    distId[startVertex].distance = 0.0f;
    THeap<TPair> vertexIds(distId, vertexCount);
    while (!vertexIds.empty())
    {
        TPair minId = vertexIds.topMin();
        TVertexId index = 0, indexX = 0, indexY = 0;
        for (int i = 0; i < edgesCount; i++)
        {
            if (edges[i].incidental(minId.vertex))
            {
                for (int j = 0; j < vertexIds.getSize(); j++)
                {
                    if (distId[j].vertex == edges[i].x)
                        indexX = j;
                    if (distId[j].vertex == edges[i].y)
                        indexY = j;
                }
                if (minId.distance + edges[i].weight < distId[indexX].distance)
                {
                    distId[indexX].distance = minId.distance + edges[i].weight;
                    up[edges[i].x] = minId.vertex;
                }
                if (minId.distance + edges[i].weight < distId[indexY].distance)
                {
                    distId[indexY].distance = minId.distance + edges[i].weight;
                    up[edges[i].y] = minId.vertex;
                }
            }
        }
        dist[minId.vertex] = minId.distance;
        vertexIds.popMin();
    }
    TPathData pathList(dist, up, vertexCount, startVertex);
    delete[] dist, delete[] up, delete[] distId;
    return pathList;
}
