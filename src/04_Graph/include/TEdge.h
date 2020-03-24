#ifndef _TEDGE_H_
#define _TEDGE_H_

#include <map>

struct TEdge
{
    int x, y;
    int weight = 0;
    TEdge() = default;
    TEdge(int x_, int y_, int weight_);
    //bool incidental(const TEdge& other) const;
    bool incidental(int vertex) const;
    bool operator> (const TEdge& edge) const { return weight > edge.weight; }
    bool operator< (const TEdge& edge) const { return weight < edge.weight; }
    bool operator>=(const TEdge& edge) const { return weight >= edge.weight; }
    bool operator<=(const TEdge& edge) const { return weight <= edge.weight; }
};

#endif