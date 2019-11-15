#ifndef _TPOLYNOMIAL_H_
#define _TPOLYNOMIAL_H_

#include <iostream>
#include <string>
#include "Monomial.h"

class TPolynomial
{
    TList<unsigned, double>* monomials;
public:
    TPolynomial();
    TPolynomial(const std::string& str);
    //TPolynomial(TList monomials);
    TPolynomial(const TPolynomial& other);
    TPolynomial(const TMonomialList& list);
    ~TPolynomial();
};

#endif //!_TPOLYNOMIAL_H_