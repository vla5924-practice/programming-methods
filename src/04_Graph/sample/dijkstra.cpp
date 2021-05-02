#include <iostream>
#include "DijkstraAlgorithm.h"

void unitTest()
{
    try
    {
        std::cout << "Test Graph 1:\n";
        TGraph graph1({
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
        std::cout << graph1;
        std::cout << "Paths Data 1:\n";
        TPathData pathData = GraphAlgorithms::dijkstraAlgorithm(graph1);
        TPathList pathList = pathData.getPaths();
        for (size_t i = 0; i < pathList.size(); i++)
        {
            std::cout << '[' << i << "] dist: " << pathData.getDist(TVertexId(i)) << " path: ";
            for (size_t j = 0; j < pathList[i].size(); j++)
                std::cout << pathList[i][j] << ' ';
            std::cout << '\n';
        }
    }
    catch (std::exception & e)
    {
        std::cerr << e.what();
    }
}

void inputTest()
{
    try
    {
        TGraph graph2;
        std::cout << "Test Graph 2:\nInput >> ";
        std::cin >> graph2;
        std::cout << graph2;
        std::cout << "Paths Data 2:\n";
        auto pathData = GraphAlgorithms::dijkstraAlgorithm(graph2);
        auto pathList = pathData.getPaths();
        for (size_t i = 0; i < pathList.size(); i++)
        {
            std::cout << '[' << i << "] dist: " << pathData.getDist(TVertexId(i)) << " path: ";
            for (size_t j = 0; j < pathList[i].size(); j++)
                std::cout << pathList[i][j] << ' ';
            std::cout << '\n';
        }
    }
    catch (std::exception & e)
    {
        std::cerr << e.what();
    }
}

int main()
{
    int mode = 1;
    std::cout << "1 - Unit Test, 2 - Input Test: ";
    std::cin >> mode;
    if (mode == 1)
        unitTest();
    else if (mode == 2)
        inputTest();
}