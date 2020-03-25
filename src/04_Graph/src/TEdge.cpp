#include "TEdge.h"

TEdge::TEdge(TVertexId x_, TVertexId y_, int weight_)
{
    x = x_;
    y = y_;
    weight = weight_;
}

bool TEdge::incidental(TVertexId vertex) const
{
    return (x == vertex) || (y == vertex);
}
