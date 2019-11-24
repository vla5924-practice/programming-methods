#ifndef _MONOMIAL_H_
#define _MONOMIAL_H_

#include <exception>
#include "TList.h"

typedef TList<unsigned, double> TMonomialList;
typedef TMonomialList::TNode TMonomial;
typedef TMonomialList::TPair TMonomialP;

namespace Monomial
{

    inline bool checkDegrees(unsigned degrees);
    inline bool checkDegrees(unsigned x, unsigned y, unsigned z);
    bool checkDegreesSum(unsigned degrees1, unsigned degrees2 = 0U);
    void rollDown(unsigned degrees, unsigned& x, unsigned& y, unsigned& z);
    inline unsigned rollUp(unsigned x, unsigned y, unsigned z);

    class DegreeOverflow : std::exception
    {
        const std::string whatStr = "Degree cannot be greater than 9.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
    class DegreeUnequality : std::exception
    {
        const std::string whatStr = "Degrees are not equal.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
}

TMonomial operator+(const TMonomial& monomial);
TMonomial operator-(const TMonomial& monomial);
TMonomial operator+(TMonomial& lhs, const TMonomial& rhs);
TMonomial operator-(TMonomial& lhs, const TMonomial& rhs);
TMonomial operator*(TMonomial& lhs, const TMonomial& rhs);
TMonomial operator*(TMonomial& lhs, const double rhs);
TMonomial operator*(double lhs, const TMonomial& rhs);

#endif //!_MONOMIAL_H_