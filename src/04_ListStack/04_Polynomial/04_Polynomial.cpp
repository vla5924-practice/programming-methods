﻿#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TPolynomial.h"
#define RND(MIN, MAX) (rand() % ((MAX) - (MIN) + 1) + (MIN))

int main()
{
    srand((unsigned)time(nullptr));
    TPolynomial poly[2];
    TMonomial monomial = Monomial::make(RND(-10, 10), RND(0, 999));
    double number = RND(-10, 10);
    int sizes[2] = { RND(3, 6), RND(3, 6) };
    int degree = RND(0, 999);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
            poly[i] += Monomial::make(RND(-10, 10), RND(0, 999));
        std::cout << '(' << i << ") " << poly[i] << '\n';
    }
    std::cout << "(2) " << TPolynomial(monomial) << '\n';
    std::cout << "(3) " << number << '\n';
    std::cout << '\n';
    std::cout << "(0) + (1) = " << (poly[0] + poly[1])  << '\n';
    std::cout << "(0) + (2) = " << (poly[0] + monomial) << '\n';
    std::cout << "(0) + (3) = " << (poly[0] + number)   << '\n';
    std::cout << "(0) - (1) = " << (poly[0] - poly[1])  << '\n';
    std::cout << "(0) - (2) = " << (poly[0] - monomial) << '\n';
    std::cout << "(0) - (3) = " << (poly[0] - number)   << '\n';
    try
    {
        std::cout << "(0) * (1) = " << (poly[0] * poly[1]) << '\n';
    }
    catch (Monomial::DegreeOverflow& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "(0) * (2) = " << (poly[0] * monomial) << '\n';
    }
    catch (Monomial::DegreeOverflow & e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "(0) * (3) = " << (poly[0] * number) << '\n';
    std::cout << "\n_poly Literal test: ";
    try
    {
        std::cout << "x + 1"_poly << '\n';

    }
    catch (TPolynomial::SyntaxError & e)
    {
        std::cerr << e.what();
    }
    std::cout << "\nEnter expression: ";
    try
    {
        TPolynomial ipoly;
        std::cin >> ipoly;
        std::cout << "Parsed: " << ipoly << '\n';

    }
    catch (TPolynomial::SyntaxError& e)
    {
        std::cerr << e.what();
    }
}