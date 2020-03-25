#ifndef _TPATHLIST_H_
#define _TPATHLIST_H_

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

    inline const float& getDist(TVertexId i) const;
    inline const TVertexId& getUp(TVertexId i) const;
    inline const TVertexId& getStartVertex() const;
    TPathList getPaths() const;
};

#endif