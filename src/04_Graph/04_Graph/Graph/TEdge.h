#ifndef _TEDGE_H_
#define _TEDGE_H_

struct TEdge
{
    int x, y;
    int weight = 0;
    bool operator>(const TEdge& edge) { return weight > edge.weight; }
    bool operator<(const TEdge& edge) { return weight < edge.weight; }
    bool operator>=(const TEdge& edge) { return weight >= edge.weight; }
    bool operator<=(const TEdge& edge) { return weight <= edge.weight; }
};

#endif