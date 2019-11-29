#include "Monomial.h"

namespace Monomial
{
    bool checkDegrees(unsigned degrees)
    {
        return degrees <= 999U;
    }

    bool checkDegrees(unsigned x, unsigned y, unsigned z)
    {
        return (x <= 9) && (y <= 9) && (z <= 9);
    }

    void rollDown(unsigned degrees, unsigned& x, unsigned& y, unsigned& z)
    {
        if (!checkDegrees(degrees))
            throw Monomial::DegreeOverflow();
        x = degrees / 100U;
        y = degrees / 10U % 10U;
        z = degrees % 10U;
    }

    unsigned rollUp(unsigned x, unsigned y, unsigned z)
    {
        return x * 100 + y * 10 + z;
    }

    TMonomial make(double coefficient, unsigned x, unsigned y, unsigned z)
    {
        if (!checkDegrees(x, y, z))
            throw DegreeOverflow();
        return TMonomial(rollUp(x, y, z), coefficient, nullptr);
    }

    TMonomial make(double coefficient, unsigned degrees)
    {
        if (!checkDegrees(degrees))
            throw DegreeOverflow();
        return TMonomial(degrees, coefficient, nullptr);
    }
}

TMonomial operator+(const TMonomial& monomial)
{
    return monomial;
}

TMonomial operator-(const TMonomial& monomial)
{
    return TMonomial(monomial.key, -1 * (*monomial.pData), monomial.pNext);
}

TMonomial operator+(TMonomial& lhs, const TMonomial& rhs)
{
    if (lhs.key != rhs.key)
        throw Monomial::DegreeUnequality();
    double coefficient = *lhs.pData + *rhs.pData;
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
    unsigned x = DEGX(lhs.key) + DEGX(rhs.key);
    unsigned y = DEGY(lhs.key) + DEGY(rhs.key);
    unsigned z = DEGZ(lhs.key) + DEGZ(rhs.key);
    if (!Monomial::checkDegrees(x, y, z))
        throw Monomial::DegreeOverflow();
    unsigned degree = Monomial::rollUp(x, y, z);
    double coefficient = (*lhs.pData) * (*rhs.pData);
    return TMonomial(degree, coefficient, lhs.pNext);
}

TMonomial operator*(TMonomial& lhs, const double rhs)
{
    return TMonomial(lhs.key, *lhs.pData * rhs, lhs.pNext);
}

TMonomial operator*(double lhs, const TMonomial& rhs)
{
    return TMonomial(rhs.key, *rhs.pData * lhs, rhs.pNext);
}