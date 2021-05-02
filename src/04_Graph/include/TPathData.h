#ifndef _TPATHDATA_H_
#define _TPATHDATA_H_

#include <vector>
using TVertexId = int;
using TPathList = std::vector<std::vector<TVertexId>>;

class TPathData
{
    float* dist;
    TVertexId* up;
    int vertexCount;
    TVertexId startVertex;
public:
    TPathData();
    TPathData(const TPathData& other);
    TPathData(TPathData&& other);
    TPathData(float*& dist_, TVertexId*& up_, int vertexCount_, TVertexId startVertex_);
    ~TPathData();

    TPathData& operator=(const TPathData& other);
    TPathData& operator=(TPathData&& other);

    inline float getDist(TVertexId i) const { return dist[i]; }
    inline TVertexId getUp(TVertexId i) const { return up[i]; }
    inline TVertexId getStartVertex() const { return startVertex; }
    TPathList getPaths() const;
};

#endif