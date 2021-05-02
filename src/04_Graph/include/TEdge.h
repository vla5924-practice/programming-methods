#ifndef _TEDGE_H_
#define _TEDGE_H_

#include <map>

using TVertexId = int;

struct TEdge
{
    TVertexId x, y;
    float weight = 0.0f;

    TEdge() = default;
    TEdge(TVertexId x_, TVertexId y_, float weight_);

    bool incidental(const TEdge& other) const;
    bool incidental(TVertexId vertex) const;
    bool like(const TEdge& other) const;

    bool operator> (const TEdge& edge) const;
    bool operator< (const TEdge& edge) const;
    bool operator>=(const TEdge& edge) const;
    bool operator<=(const TEdge& edge) const;
};

#endif