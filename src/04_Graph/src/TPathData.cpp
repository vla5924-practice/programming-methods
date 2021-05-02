#include "TPathData.h"

TPathData::TPathData()
{
    dist = nullptr;
    up = nullptr;
    vertexCount = 0;
    startVertex = 0;
}

TPathData::TPathData(const TPathData& other)
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

TPathData::TPathData(TPathData&& other)
{
    vertexCount = other.vertexCount;
    startVertex = other.startVertex;
    dist = other.dist;
    up = other.up;
    other.vertexCount = 0;
    other.dist = nullptr;
    other.up = nullptr;
}

TPathData::TPathData(float*& dist_, TVertexId*& up_, int vertexCount_, TVertexId startVertex_)
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

TPathData::~TPathData()
{
    if (dist)
        delete[] dist;
    if (up)
        delete[] up;
}

TPathData& TPathData::operator=(const TPathData& other)
{
    if (this == &other)
        return *this;
    if (dist)
        delete[] dist;
    if (up)
        delete[] up;
    vertexCount = other.vertexCount;
    startVertex = other.startVertex;
    dist = new float[vertexCount];
    up = new TVertexId[vertexCount];
    for (TVertexId i = 0; i < vertexCount; i++)
    {
        dist[i] = other.dist[i];
        up[i] = other.up[i];
    }
    return *this;
}

TPathData& TPathData::operator=(TPathData&& other)
{
    if (this == &other)
        return *this;
    if (dist)
        delete[] dist;
    if (up)
        delete[] up;
    vertexCount = other.vertexCount;
    startVertex = other.startVertex;
    dist = other.dist;
    up = other.up;
    other.vertexCount = 0;
    other.dist = nullptr;
    other.up = nullptr;
    return *this;
}

TPathList TPathData::getPaths() const
{
    std::vector<float> tempDist(dist, dist + vertexCount);
    TPathList paths;
    paths.resize(vertexCount - 1);
    for (int i = 0; i < vertexCount; i++)
    {
        float maxDist = tempDist[0];
        TVertexId maxDistId = 0;
        for (int j = 1; j < vertexCount; j++)
            if (maxDist < tempDist[j])
            {
                maxDist = tempDist[j];
                maxDistId = j;
            }
        tempDist[maxDistId] = -1;
        if (maxDistId == startVertex)
            continue;
        TVertexId vertex = maxDistId;
        while (vertex != startVertex)
        {
            paths[i].push_back(vertex);
            vertex = up[vertex];
        }
        paths[i].push_back(startVertex);
        std::reverse(paths[i].begin(), paths[i].end());
    }
    return paths;
}
