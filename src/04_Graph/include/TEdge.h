#ifndef _TEDGE_H_
#define _TEDGE_H_

#include <map>

using TVertexId = int;

struct TEdge
{
    TVertexId x, y;
    int weight = 0;
    TEdge() = default;
    TEdge(TVertexId x_, TVertexId y_, int weight_);
    //bool incidental(const TEdge& other) const;
    bool incidental(TVertexId vertex) const;
    bool operator> (const TEdge& edge) const { return weight > edge.weight; }
    bool operator< (const TEdge& edge) const { return weight < edge.weight; }
    bool operator>=(const TEdge& edge) const { return weight >= edge.weight; }
    bool operator<=(const TEdge& edge) const { return weight <= edge.weight; }
};

#endif