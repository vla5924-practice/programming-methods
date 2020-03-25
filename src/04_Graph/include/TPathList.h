#ifndef _TPATHLIST_H_
#define _TPATHLIST_H_

#include <vector>
using TVertexId = int;

class TPathList
{
    float* dist;
    TVertexId* up;
    int vertexCount;
    TVertexId startVertex;
public:
    TPathList();
    TPathList(const TPathList& other);
    TPathList(TPathList&& other);
    TPathList(float*& dist_, TVertexId*& up_, int vertexCount_, TVertexId startVertex_);
    ~TPathList();

    inline const float& getDist(TVertexId i) const;
    inline const TVertexId& getUp(TVertexId i) const;
    inline const TVertexId& getStartVertex() const;
    std::vector<std::vector<TVertexId>> getPaths() const;
};

#endif