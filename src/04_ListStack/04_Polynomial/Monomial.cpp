#include "Monomial.h"

Monomial::TDegrees::TDegrees(unsigned x, unsigned y, unsigned z) : x(x), y(y), z(z)
{
}

bool Monomial::checkDegrees(unsigned degrees)
{
    return degrees <= 999U;
}

bool Monomial::checkDegrees(TDegrees degrees)
{
    return (degrees.x <= 9U) && (degrees.y <= 9U) && (degrees.z <= 9U);
}

bool Monomial::checkDegreesSum(unsigned degrees1, unsigned degrees2)
{
    TDegrees degreesR1 = rollDown(degrees1);
    TDegrees degreesR2 = rollDown(degrees2);
    TDegrees result(degreesR1.x + degreesR2.x, degreesR1.y + degreesR2.y, degreesR1.z + degreesR2.z);
    if (!checkDegrees(result))
        return false;
    return true;
}

Monomial::TDegrees Monomial::rollDown(unsigned degrees)
{
    if (!checkDegrees(degrees))
        throw DegreeOverflow();
    unsigned x = degrees / 100U;
    unsigned y = degrees / 10U % 10U;
    unsigned z = degrees % 10U;
    return TDegrees(x, y, z);
}

unsigned Monomial::rollUp(TDegrees degrees)
{
    if (!checkDegrees(degrees))
        throw DegreeOverflow();
}


TMonomial operator+(TMonomial& lhs, const TMonomial& rhs)
{
    if (lhs.key != rhs.key)
        throw Monomial::DegreeUnequality();
    double coefficient = *(lhs.pData) + *(rhs.pData);
    return TMonomial(lhs.key, coefficient, lhs.pNext);
}

TMonomial operator-(TMonomial& lhs, const TMonomial& rhs)
{
    if (lhs.key != rhs.key)
        throw Monomial::DegreeUnequality();
    double coefficient = *(lhs.pData) - *(rhs.pData);
    return TMonomial(lhs.key, coefficient, lhs.pNext);
}

TMonomial operator*(TMonomial& lhs, const TMonomial& rhs)
{
    if (!Monomial::checkDegrees(lhs.key + rhs.key))
        throw Monomial::DegreeOverflow();
    double coefficient = *(lhs.pData) - *(rhs.pData);
    return TMonomial(lhs.key, coefficient, lhs.pNext);
}