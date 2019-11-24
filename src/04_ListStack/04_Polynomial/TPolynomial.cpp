#include "TPolynomial.h"

TMonomialList::iterator TPolynomial::findPrevOrderedDegree(unsigned degree) const
{
    auto temp = monomials->begin();
    for (auto i = monomials->begin(); i != monomials->end(); i++)
    {
        temp = i;
        auto j = temp;
        j++;
        if ((*j).key < degree)
            return temp;
    }
    return temp;
}

TPolynomial::TPolynomial()
{
    monomials = new TMonomialList;
}

TPolynomial::TPolynomial(const std::string& str) : TPolynomial()
{
    parse(str);
}

TPolynomial::TPolynomial(const TPolynomial& other)
{
    monomials = new TMonomialList(*other.monomials);
}

TPolynomial::TPolynomial(const TMonomialList& list)
{
    // some check degs...
    monomials = new TMonomialList(list);
}

TPolynomial::~TPolynomial()
{
    delete monomials;
}

TPolynomial& TPolynomial::operator=(const TPolynomial& other)
{
    delete monomials;
    monomials = new TMonomialList(*other.monomials);
}

TPolynomial TPolynomial::operator+(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (auto i : *result.monomials)
    {
        TMonomialP monomial = other.monomials->find(i.key);
        if (monomial)
            *i.pData += *monomial.pData;
        else
            result.monomials->insertAfter(findPrevOrderedDegree(i.key), i.key, i.pData);
    }
    return result;
}
