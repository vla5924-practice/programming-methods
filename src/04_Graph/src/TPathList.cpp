#include "TPathList.h"

TPathList::TPathList()
{
    dist = nullptr;
    up = nullptr;
    vertexCount = 0;
    startVertex = 0;
}

TPathList::TPathList(const TPathList& other)
{
    vertexCount = other.vertexCount;
    startVertex = other.startVertex;
    dist = new float[vertexCount];
    up = new TVertexId[vertexCount];
    for (TVertexId i = 0; i < vertexCount; i++)
    {
        dist[i] = other.dist[i];
        up[i] = other.up[i];
    }
}

TPathList::TPathList(TPathList&& other)
{
    vertexCount = other.vertexCount;
    startVertex = other.startVertex;
    dist = other.dist;
    up = other.up;
    other.vertexCount = 0;
    other.dist = nullptr;
    other.up = nullptr;
}

TPathList::TPathList(float*& dist_, TVertexId*& up_, int vertexCount_, TVertexId startVertex_)
{
    vertexCount = vertexCount_;
    startVertex = startVertex_;
    dist = new float[vertexCount];
    up = new TVertexId[vertexCount];
    for (TVertexId i = 0; i < vertexCount; i++)
    {
        dist[i] = dist_[i];
        up[i] = up_[i];
    }
}

TPathList::~TPathList()
{
    if (dist)
        delete[] dist;
    if (up)
        delete[] up;
}

const float& TPathList::getDist(TVertexId i) const
{
    return dist[i];
}

const TVertexId& TPathList::getUp(TVertexId i) const
{
    return up[i];
}

const TVertexId& TPathList::getStartVertex() const
{
    return startVertex;
}

std::vector<std::vector<TVertexId>> TPathList::getPaths() const
{
    std::vector<std::vector<TVertexId>> paths;
    paths.resize(vertexCount - 1);
    for (int i = 0; i < vertexCount; i++)
    {
        float maxDistation = dist[0];
        int maxDistationIndex = 0;
        for (int j = 1; j < vertexCount; j++)
            if (maxDistation < dist[j])
            {
                maxDistation = dist[j];
                maxDistationIndex = j;
            }
        dist[maxDistationIndex] = -1;
        if (maxDistationIndex == startVertex)
            continue;
        int v = maxDistationIndex;
        while (v != startVertex)
        {
            paths[i].push_back(v);
            v = up[v];
        }
        paths[i].push_back(startVertex);
        std::reverse(paths[i].begin(), paths[i].end());
    }
    return paths;
}
