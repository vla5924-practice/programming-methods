#include <iostream>
#include "TGraph.h"

int main()
{
    TGraph graph1({
        TEdge(1, 4, 0),
        TEdge(1, 3, 1),
        TEdge(2, 4, 2),
        TEdge(0, 5, 2),
        TEdge(1, 5, 2),
        TEdge(0, 4, 3),
        TEdge(3, 4, 4),
        TEdge(2, 3, 5),
        TEdge(0, 1, 8),
        TEdge(2, 5, 9),
        TEdge(1, 2, 10)
        }, 6);
    graph1.kruskalAlgorithm().output();

    TGraph graph2({
        TEdge(0, 1, 5),
        TEdge(1, 2, 2),
        TEdge(0, 2, 8),
        TEdge(1, 4, 5),
        TEdge(2, 4, 2),
        TEdge(0, 3, 11),
        TEdge(2, 3, 3),
        TEdge(3, 5, 8),
        TEdge(4, 5, 6),
        TEdge(4, 7, 1),
        TEdge(5, 6, 13),
        TEdge(5, 7, 24),
        TEdge(6, 7, 5)
        }, 8);
    /*int* dist, * up;
    graph1.dijkstraAlgorithm(dist, up);
    for (int i = 0; i < graph1.vertexCount; i++)
        std::cout << dist[i] << ' ';
    std::cout << '\n';
    for (int i = 0; i < graph1.vertexCount; i++)
        std::cout << up[i] << ' ';
    std::cout << '\n';*/
}
