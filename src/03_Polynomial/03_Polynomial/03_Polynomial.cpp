﻿#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TPolynomial.h"
#define RND(MIN, MAX) (rand() % ((MAX) - (MIN) + 1) + (MIN))

void testMode();
void calcMode();

int main()
{
    std::cout << "0 - Test Mode, 1 - Calc Mode: ";
    int menu;
    std::cin >> menu;
    std::cin.ignore(1);
    if (menu == 0)
        testMode();
    else
        calcMode();
    std::cin.ignore(1);
    return 0;
}

void testMode()
{
    srand((unsigned)time(nullptr));
    TPolynomial poly[2];
    TMonomial monomial = TMonomial(static_cast<double>(RND(-10, 10)), RND(0, 999));
    double number = RND(-10, 10);
    int sizes[2] = { RND(3, 6), RND(3, 6) };
    int degree = RND(0, 999);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
            poly[i] += TMonomial(static_cast<double>(RND(-10, 10)), RND(0, 999));
        std::cout << '(' << i << ") " << poly[i] << '\n';
    }
    std::cout << "(2) " << TPolynomial(monomial) << '\n';
    std::cout << "(3) " << number << '\n';
    std::cout << '\n';
    std::cout << "(0) + (1) = " << (poly[0] + poly[1]) << '\n';
    std::cout << "(0) + (2) = " << (poly[0] + monomial) << '\n';
    std::cout << "(0) + (3) = " << (poly[0] + number) << '\n';
    std::cout << "(0) - (1) = " << (poly[0] - poly[1]) << '\n';
    std::cout << "(0) - (2) = " << (poly[0] - monomial) << '\n';
    std::cout << "(0) - (3) = " << (poly[0] - number) << '\n';
    try
    {
        std::cout << "(0) * (1) = " << (poly[0] * poly[1]) << '\n';
    }
    catch (TMonomial::DegreeOverflow & e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        std::cout << "(0) * (2) = " << (poly[0] * monomial) << '\n';
    }
    catch (TMonomial::DegreeOverflow & e)
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
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }
    TList<unsigned, double> l;
    l.insertToEnd(0U, 1);
    l.insertToEnd(150U, 3);
    l.insertToEnd(350U, 5);
    TPolynomial sp = l;
    std::cout << sp;
}

void calcMode()
{
    TPolynomial lhs, rhs;
    bool success;
    std::cout << "Enter polynom 1: ";
    success = false;
    do
    {
        try
        {
            std::cin >> lhs;
            std::cout << "Parsed: " << lhs << '\n';
            success = true;
        }
        catch (...)
        {
            std::cerr << "Syntax Error.";
            std::cout << " Try again: ";
        }
    } while (!success);
    std::cout << "Enter polynom 2: ";
    success = false;
    do
    {
        try
        {
            std::cin >> rhs;
            std::cout << "Parsed: " << rhs << '\n';
            success = true;
        }
        catch (...)
        {
            std::cerr << "Syntax Error.";
            std::cout << " Try again: ";
        }
    } while (!success);
    std::cout << "Result: \n";
    try
    {
        std::cout << "(+): " << (lhs + rhs) << '\n';
        std::cout << "(-): " << (lhs - rhs) << '\n';
        std::cout << "(*): " << (lhs * rhs) << '\n';
    }
    catch (...)
    {
        std::cerr << "Degree overflow.";
    }
    std::cout << '\n';
}