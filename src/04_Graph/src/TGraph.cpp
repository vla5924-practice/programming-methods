#include "TGraph.h"

bool TGraph::connected(const TAdjacencyMatrix& adjMatrix) const
{
    TAdjacencyList adjList(vertexCount);
    for (int i = 0; i < vertexCount; i++)
        for (int j = i + 1; j < vertexCount; j++)
            if (adjMatrix[i][j] == true)
            {
                adjList.add(i, j);
                adjList.add(j, i);
            }
    // Use BFS to check if graph has one connectivity component
    std::vector<bool> vertexUsed;
    vertexUsed.resize(vertexCount, false);
    std::queue<TVertexId> vertexQueue;
    vertexQueue.push(0);
    vertexUsed[0] = true;
    while (!vertexQueue.empty())
    {
        int vertex = vertexQueue.front();
        vertexQueue.pop();
        for (size_t i = 0; i < adjList[vertex].size(); ++i)
        {
            int adjacentVertex = adjList[vertex][i];
            if (!vertexUsed[adjacentVertex])
            {
                vertexUsed[adjacentVertex] = true;
                vertexQueue.push(adjacentVertex);
            }
        }
    }
    // If there are vertexes not used in BFS then graph is not connected
    bool isGraphConnected = true;
    for (size_t i = 0; i < vertexUsed.size(); i++)
        if (!vertexUsed[i])
        {
            isGraphConnected = false;
            break;
        }
    return isGraphConnected;
}

TAdjacencyMatrix TGraph::generateAdjacencyMatrix() const
{
    TAdjacencyMatrix adjMatrix(vertexCount);
    for (int i = 0; i < edgesCount; i++)
    {
        if ((adjMatrix[edges[i].x][edges[i].y] == false) && (adjMatrix[edges[i].y][edges[i].x] == false))
        {
            adjMatrix[edges[i].x][edges[i].y] = true;
            adjMatrix[edges[i].y][edges[i].x] = true;
        }
    }
    return adjMatrix;
}

void TGraph::freeEdges()
{
    if (edges)
        delete[] edges;
    edgesCount = 0;
    edges = nullptr;
}

TGraph::TGraph() : edges(nullptr), vertexCount(0), edgesCount(0)
{
}

TGraph::TGraph(const TGraph& other)
{
    vertexCount = other.vertexCount;
    edgesCount = other.edgesCount;
    edges = new TEdge[edgesCount];
    for (int i = 0; i < edgesCount; i++)
        edges[i] = other.edges[i];
}

TGraph::TGraph(TGraph&& other)
{
    vertexCount = other.vertexCount;
    edgesCount = other.edgesCount;
    edges = other.edges;
    other.vertexCount = 0;
    other.edgesCount = 0;
    other.edges = nullptr;
}

TGraph::TGraph(std::initializer_list<TEdge> edgesList, int vertexCount_)
{
    if (vertexCount_ < 0)
        throw InvalidParameterError();
    vertexCount = vertexCount_;
    edgesCount = static_cast<int>(edgesList.size());
    edges = new TEdge[edgesCount];
    int i = 0;
    for (const TEdge& edge : edgesList)
    {
        edges[i++] = edge;
    }
    TAdjacencyMatrix adjMatrix = generateAdjacencyMatrix();
    for (int i = 0; i < edgesCount; i++)
    {
        if (edges[i].x == edges[i].y)
        {
            freeEdges();
            throw SelfLoopedGraphError();
        }
        if (adjMatrix[edges[i].x][edges[i].y] != adjMatrix[edges[i].y][edges[i].x])
        {
            freeEdges();
            throw DirectedGraphError();
        }
    }
    if (!connected(adjMatrix))
    {
        freeEdges();
        throw MulticonnectedGraphError();
    }
}

TGraph::TGraph(TEdge* edges_, int edgesCount_, int vertexCount_)
{
    if ((vertexCount_ < 0) || (edgesCount_ < 0))
        throw InvalidParameterError();
    vertexCount = vertexCount_;
    edgesCount = edgesCount_;
    edges = new TEdge[edgesCount];
    for (int i = 0; i < edgesCount; i++)
    {
        edges[i] = edges_[i];
    }
    TAdjacencyMatrix adjMatrix = generateAdjacencyMatrix();
    for (int i = 0; i < edgesCount; i++)
    {
        if (edges[i].x == edges[i].y)
        {
            freeEdges();
            throw SelfLoopedGraphError();
        }
        if (adjMatrix[edges[i].x][edges[i].y] != adjMatrix[edges[i].y][edges[i].x])
        {
            freeEdges();
            throw DirectedGraphError();
        }
    }
    if (!connected(adjMatrix))
    {
        freeEdges();
        throw MulticonnectedGraphError();
    }
}

TGraph::~TGraph()
{
    freeEdges();
}

TGraph& TGraph::operator=(const TGraph& other)
{
    if ((this == &other) || (*this == other))
        return *this;
    freeEdges();
    vertexCount = other.vertexCount;
    edgesCount = other.edgesCount;
    edges = new TEdge[edgesCount];
    for (int i = 0; i < edgesCount; i++)
        edges[i] = other.edges[i];
    return *this;
}

TGraph& TGraph::operator=(TGraph&& other)
{
    if (this == &other)
        return *this;
    freeEdges();
    vertexCount = other.vertexCount;
    edgesCount = other.edgesCount;
    edges = other.edges;
    other.vertexCount = 0;
    other.edgesCount = 0;
    other.edges = nullptr;
    return *this;
}

bool TGraph::operator==(const TGraph& other) const
{
    if ((vertexCount != other.vertexCount) || (edgesCount != other.edgesCount))
        return false;
    if (edges == other.edges)
        return true;
    for (int i = 0; i < edgesCount; i++)
    {
        bool found = false;
        for (int j = 0; j < edgesCount; j++)
            if (edges[i].like(edges[j]))
                found = true;
        if (!found)
            return false;
    }
    return true;
}

bool TGraph::operator!=(const TGraph& other) const
{
    return !(*this == other);
}

bool TGraph::hasEdge(TVertexId x, TVertexId y) const
{
    for (int i = 0; i < edgesCount; i++)
        if (edges[i].incidental(x) && edges[i].incidental(y))
            return true;
    return false;
}

TEdgeList TGraph::getEdges() const
{
    TEdgeList list(edgesCount);
    for (int i = 0; i < edgesCount; i++)
        list[i] = edges[i];
    return list;
}

TEdgeList TGraph::getEdges(TEdgeFilterFunc filter) const
{
    TEdgeList list;
    for (int i = 0; i < edgesCount; i++)
        if((*filter)(edges[i]))
            list.push_back(edges[i]);
    return list;
}

float TGraph::getWeight() const
{
    float weight = 0.0f;
    for (int i = 0; i < edgesCount; i++)
        weight += edges[i].weight;
    return weight;
}

float TGraph::getWeight(TEdgeFilterFunc filter) const
{
    float weight = 0.0f;
    for (int i = 0; i < edgesCount; i++)
        if((*filter)(edges[i]))
            weight += edges[i].weight;
    return weight;
}

std::ostream& operator<<(std::ostream& output, const TGraph& graph)
{
    std::cout << "[\n";
    for (int i = 0; i < graph.edgesCount; i++)
        std::cout << "    (" << graph.edges[i].x << ", " << graph.edges[i].y << ") {" << graph.edges[i].weight << "}\n";
    std::cout << "]\n";
    return output;
}

std::istream& operator>>(std::istream& input, TGraph& graph)
{
    int vertexCount_ = 0, edgesCount_ = 0;
    input >> vertexCount_ >> edgesCount_;
    if ((vertexCount_ < 0) || (edgesCount_ < 0))
        throw TGraph::InvalidParameterError();
    TEdge* edges_ = new TEdge[edgesCount_];
    for (int i = 0; i < edgesCount_; i++)
        input >> edges_[i].x >> edges_[i].y >> edges_[i].weight;
    graph = TGraph(edges_, edgesCount_, vertexCount_);
    return input;
}
