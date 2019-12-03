#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TPolynomial.h"
#define RND(MIN, MAX) (rand() % ((MAX) - (MIN) + 1) + (MIN))

int main()
{
    TPolynomial poly[3];
    TMonomial monomial = Monomial::make(RND(-10, 10), RND(0, 999));
    double number = RND(-10, 10);
    int sizes[3] = { RND(3, 8), RND(3, 8), RND(3, 8) };
    int degree = RND(0, 999);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
            poly[i] += Monomial::make(RND(-10, 10), RND(0, 999));
        std::cout << poly[i] << '\n';
    }
    std::cout << '\n';
    try
    {
        std::cout << "xz + y"_poly << '\n';
        TPolynomial ip;
        std::cin >> ip;
        std::cout << ip;
    }
    catch (TPolynomial::SyntaxError & e)
    {
        std::cerr << e.what();
    }
}