#include "TEdge.h"

TEdge::TEdge(TVertexId x_, TVertexId y_, float weight_)
{
    x = x_;
    y = y_;
    weight = weight_;
}

bool TEdge::incidental(const TEdge& other) const
{
    return incidental(other.x) || incidental(other.y);
}

bool TEdge::incidental(TVertexId vertex) const
{
    return (x == vertex) || (y == vertex);
}

bool TEdge::operator>(const TEdge& edge) const
{
    return weight > edge.weight;
}

bool TEdge::operator<(const TEdge& edge) const
{
    return weight < edge.weight;
}

bool TEdge::operator>=(const TEdge& edge) const
{
    return weight >= edge.weight;
}

bool TEdge::operator<=(const TEdge& edge) const
{
    return weight <= edge.weight;
}