#ifndef _TMONOMIAL_H_
#define _TMONOMIAL_H_

#define DEGX(A) ((A) / 100U)
#define DEGY(A) ((A) / 10U % 10U)
#define DEGZ(A) ((A) % 10U)
#define MAKEDEG(X, Y, Z) ((X) * 100U + (Y) * 10U + (Z))

#include "TList.h"

typedef TList<unsigned, double> TMonomialList;
typedef TMonomialList::TNode TMonomial;

template<>
class TList<unsigned, double>::TNode
{
    template <typename, typename> friend class TList;
    template <typename> friend class TListIterator;
    TNode* pNext;
    bool checkDegrees(unsigned degrees)
    {
        return degrees <= 999U;
    }
    bool checkDegrees(unsigned x, unsigned y, unsigned z)
    {
        return (x <= 9) && (y <= 9) && (z <= 9);
    }
public:
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

    unsigned key;
    double* pData;
    explicit TNode(unsigned key_ = 0U, double* pData_ = nullptr, TNode* pNext_ = nullptr)
    {
        if (key_ > 999U)
            throw DegreeOverflow();
        key = key_;
        pData = pData_ ? pData_ : new double(0.);
        pNext = pNext_;
    }
    TNode(unsigned key_, double data, TNode* pNext_ = nullptr)
    {
        if (key_ > 999U)
            throw DegreeOverflow();
        key = key_;
        pData = new double(data);
        pNext = pNext_;
    }
    TNode(const TNode& other)
        : key(other.key), pData(other.pData ? new double(*(other.pData)) : nullptr), pNext(other.pNext)
    {

    }
    TNode(double coefficient, unsigned degree) : TNode(degree, coefficient)
    {
    }
    TNode operator+(const TNode& other)
    {
        if (key != other.key)
            throw DegreeUnequality();
        double coefficient = *pData + *other.pData;
        return TMonomial(key, coefficient, pNext);
    }
    TNode operator-(const TNode& other)
    {
        if (key != other.key)
            throw DegreeUnequality();
        double coefficient = *pData - *other.pData;
        return TMonomial(key, coefficient, pNext);
    }
    TNode operator*(const TNode& other)
    {
        if (!checkDegrees(key + other.key))
            throw DegreeOverflow();
        unsigned x = DEGX(key) + DEGX(other.key);
        unsigned y = DEGY(key) + DEGY(other.key);
        unsigned z = DEGZ(key) + DEGZ(other.key);
        if (!checkDegrees(x, y, z))
            throw DegreeOverflow();
        unsigned degree = MAKEDEG(x, y, z);
        double coefficient = (*pData) * (*other.pData);
        return TMonomial(degree, coefficient, pNext);
    }
    TNode operator*(double number)
    {
        return TMonomial(key, *pData * number, pNext);
    }
};

#endif //!_TMONOMIAL_H_
