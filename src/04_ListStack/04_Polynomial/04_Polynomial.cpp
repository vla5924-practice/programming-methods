#include "TPolynomial.h"

int main()
{
    std::cout << "3.45*x 3 y 2 - 45*y^3*z^6*x^7 + 4.700"_poly << '\n'; // kojima genius
    TPolynomial p;
    p = p + 3;
    p = p + Monomial::make(2, 246);
    p = p + p;
    std::cout << p << '\n';
    p = "x + 1"_poly * 2;
    std::cout << p << '\n';
}