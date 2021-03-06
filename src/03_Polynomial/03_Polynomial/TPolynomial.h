﻿#ifndef _TPOLYNOMIAL_H_
#define _TPOLYNOMIAL_H_

#include <iostream>
#include "TMonomial.h"

class TPolynomial
{
    TList<unsigned, double>* monomials;
    TMonomialList::iterator findPrevOrderedDegree(unsigned degree) const;
    TMonomialList::iterator getNextIterator(TMonomialList::iterator iterator) const;
    void add(double coefficient, unsigned degree);
    void addNonzero(TMonomial* primary, const TMonomial* secondary);
    void reduce();
    void sort();
    void nullify();
    void parse(const char* const expression);
    const std::string monomToStr(const TMonomial& monomial) const;
    const std::string getFirstFloatNumber(const char* const expression, size_t& offset) const;
    const std::string getFirstUIntNumber(const char* const expression, size_t& offset) const;
    unsigned getDegreeMask(const char* const expression, unsigned& factor) const;
public:
    TPolynomial();
    TPolynomial(const char* const expression);
    TPolynomial(const TMonomial& monomial);
    TPolynomial(double number);
    TPolynomial(const TPolynomial& other);
    TPolynomial(const TMonomialList& list);
    ~TPolynomial();
    TPolynomial& operator=(const TPolynomial& other);
    TPolynomial operator+(const TPolynomial& other);
    TPolynomial operator+(const TMonomial& monomial);
    TPolynomial operator+(double number);
    TPolynomial operator-(const TPolynomial& other);
    TPolynomial operator-(const TMonomial& monomial);
    TPolynomial operator-(double number);
    TPolynomial operator*(const TPolynomial& other);
    TPolynomial operator*(const TMonomial& monomial);
    TPolynomial operator*(double number);
    TPolynomial& operator+=(const TPolynomial& other);
    TPolynomial& operator+=(const TMonomial& monomial);
    TPolynomial& operator+=(double number);
    TPolynomial& operator-=(const TPolynomial& other);
    TPolynomial& operator-=(const TMonomial& monomial);
    TPolynomial& operator-=(double number);
    TPolynomial& operator*=(const TPolynomial& other);
    TPolynomial& operator*=(const TMonomial& monomial);
    TPolynomial& operator*=(double number);
    friend std::ostream& operator<<(std::ostream& stream, const TPolynomial& polynomial);
    friend std::istream& operator>>(std::istream& stream, TPolynomial& polynomial);
    class SyntaxError : std::exception
    {
        const std::string whatStr = "Serialization cannot be parsed.";
    public:
        virtual const char* what() { return whatStr.c_str(); }
    };
};

TPolynomial operator ""_poly(const char* literal, size_t);

#endif //!_TPOLYNOMIAL_H_