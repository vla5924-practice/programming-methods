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

private:
    template <typename, typename> friend class TList;
    template <typename> friend class TListIterator;
    TNode* pNext;

    bool checkDegrees(unsigned degrees) const
    {
        return degrees <= 999U;
    }

    bool checkDegrees(unsigned x, unsigned y, unsigned z) const
    {
        return (x <= 9) && (y <= 9) && (z <= 9);
    }

public:
    unsigned key;
    double data;

    explicit TNode(unsigned degree = 0U, double coefficient = 0., TNode* pNext_ = nullptr)
    {
        if (degree > 999U)
            throw DegreeOverflow();
		key = degree;
        data = coefficient;
        pNext = pNext_;
    }
	TNode(const TNode&) = default;
	TNode(double coefficient, unsigned degree) : TNode(degree, coefficient) {};

    TNode operator+(const TNode& other) const
    {
        if (key != other.key)
            throw DegreeUnequality();
        double coefficient = data + other.data;
        return TMonomial(key, coefficient, pNext);
    }

    TNode operator-(const TNode& other) const
    {
        if (key != other.key)
            throw DegreeUnequality();
        double coefficient = data - other.data;
        return TMonomial(key, coefficient, pNext);
    }

    TNode operator*(const TNode& other) const
    {
        if (!checkDegrees(key + other.key))
            throw DegreeOverflow();
        unsigned x = DEGX(key) + DEGX(other.key);
        unsigned y = DEGY(key) + DEGY(other.key);
        unsigned z = DEGZ(key) + DEGZ(other.key);
        if (!checkDegrees(x, y, z))
            throw DegreeOverflow();
        unsigned degree = MAKEDEG(x, y, z);
		double coefficient = data * other.data;
        return TMonomial(degree, coefficient, pNext);
    }

    TNode operator*(double number) const
    {
        return TMonomial(key, data * number, pNext);
    }

	TNode operator+() const
	{
		return *this;
	}

	TNode operator-() const
	{
		return TNode(key, -data, pNext);
	}
};

#endif //!_TMONOMIAL_H_
