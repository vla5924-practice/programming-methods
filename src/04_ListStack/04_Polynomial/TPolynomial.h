#ifndef _TPOLYNOMIAL_H_
#define _TPOLYNOMIAL_H_

#include <iostream>
#include <string>
#include "Monomial.h"

class TPolynomial
{
    TList<unsigned, double>* monomials;
    TMonomialList::iterator findPrevOrderedDegree(unsigned degree) const;
public:
    TPolynomial();
    TPolynomial(const std::string& str);
    TPolynomial(const TPolynomial& other);
    TPolynomial(const TMonomialList& list);
    ~TPolynomial();

    TPolynomial& operator=(const TPolynomial& other);
    TPolynomial operator+(const TPolynomial& other);
    TPolynomial operator+(const TMonomial& monomial);
    TPolynomial operator+(const TMonomialP& monomial);
    TPolynomial operator+(double number);
    TPolynomial operator-(const TPolynomial& other);
    TPolynomial operator-(const TMonomial& monomial);
    TPolynomial operator-(const TMonomialP& monomial);
    TPolynomial operator-(double number);
    TPolynomial operator*(const TPolynomial& other);
    TPolynomial operator*(const TMonomial& monomial);
    TPolynomial operator*(const TMonomialP& monomial);
    TPolynomial operator*(double number);

    friend std::ostream& operator<<(std::ostream& stream, const TPolynomial& polynomial);
    friend std::istream& operator>>(std::istream& stream, TPolynomial& polynomial);

    void parse(const std::string str);
};

//TPolynomial operator""_poly(const char* str);

#endif //!_TPOLYNOMIAL_H_