#include "TPolynomial.h"

TMonomialList::iterator TPolynomial::findPrevOrderedDegree(unsigned degree) const
{
    TMonomialList::iterator temp = monomials->begin();
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        temp = i;
        TMonomialList::iterator j = getNextIterator(temp);
        if ((*j).key < degree)
            return temp;
    }
    return temp;
}

TMonomialList::iterator TPolynomial::getNextIterator(TMonomialList::iterator iterator) const
{
    return iterator++;
}

void TPolynomial::add(double coefficient, unsigned degree)
{
    double* pCoef = new double(coefficient);
    monomials->insertAfter(findPrevOrderedDegree(degree), degree, pCoef);
    delete pCoef;
}

void TPolynomial::add(double* pCoef, unsigned degree)
{
    monomials->insertAfter(findPrevOrderedDegree(degree), degree, pCoef);
}

void TPolynomial::reduce()
{
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomialP control = *i;
        for (TMonomialList::iterator j = getNextIterator(i); j != monomials->end(); j++)
        {
            TMonomialP monomial = *j;
            if (monomial.key == control.key)
            {
                *control.pData += *monomial.pData;
                monomials->remove(j);
            }
        }
    }
}

void TPolynomial::nullify()
{
    monomials->removeAll();
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
    for (TMonomialList::iterator i = list.begin(); i != list.end(); i++)
        if (!Monomial::checkDegrees((*i).key))
            throw Monomial::DegreeOverflow();
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
    return *this;
}

TPolynomial TPolynomial::operator+(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        TMonomialP monomial = other.monomials->find(current.key);
        if (monomial)
            *current.pData += *monomial.pData;
        else
            result.add(*current.pData, current.key);
    }
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomialP needle = result.monomials->find(monomial.key);
    if (needle)
        *needle.pData += *monomial.pData;
    else
        result.add(monomial.pData, monomial.key);
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomialP& monomial)
{
    return *this;
    //return *this + Monomial::make(*monomial.pData, monomial.key);
}

TPolynomial TPolynomial::operator+(double number)
{
    return *this;
    //return *this + Monomial::make(number, 0U);
}

TPolynomial TPolynomial::operator-(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        TMonomialP monomial = other.monomials->find(current.key);
        if (monomial)
            *current.pData -= *monomial.pData;
        else
            result.add(*current.pData, current.key);
    }
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomialP needle = result.monomials->find(monomial.key);
    if (needle)
        *needle.pData -= *monomial.pData;
    else
        result.add(monomial.pData, monomial.key);
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomialP& monomial)
{
    return *this;
    //return *this - Monomial::make(*monomial.pData, monomial.key);
}

TPolynomial TPolynomial::operator-(double number)
{
    return *this;
    //return *this - Monomial::make(number, 0U);
}

TPolynomial TPolynomial::operator*(double number)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        *current.pData *= number;
    }
    return result;
}

void TPolynomial::parse(const std::string str)
{

}
