#include "TEdge.h"

TEdge::TEdge(int x_, int y_, int weight_)
{
    x = x_;
    y = y_;
    weight = weight_;
}

bool TEdge::incidental(int vertex) const
{
    return (x == vertex) || (y == vertex);
}
