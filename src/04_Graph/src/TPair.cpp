#include "TPair.h"

bool TPair::operator<(const TPair& other) const
{
    return distance < other.distance;
}

bool TPair::operator<=(const TPair& other) const
{
    return distance <= other.distance;
}

bool TPair::operator>(const TPair& other) const
{
    return distance > other.distance;
}

bool TPair::operator>=(const TPair& other) const
{
    return distance >= other.distance;
}

bool TPair::operator==(const TPair& other) const
{
    return (vertex == other.vertex) && (distance == other.distance);
}

bool TPair::operator!=(const TPair& other) const
{
    return !(*this == other);
}
