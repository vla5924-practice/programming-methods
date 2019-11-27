#include "TPolynomial.h"

int main()
{
    std::cout << "3.45*x 3 y 2 - 45*y^3*z^6*x^7 + 4.700"_poly << '\n'; // kojima genius
    std::cout << "3.45*x 3 y 2 - 45*y^3*z^6*x^7 + 4.700"_poly << '\n'; // kojima genius
    TPolynomial p;
    p = p + 3;
    p = p + Monomial::make(2, 246);
    p = p + p;
    std::cout << p << '\n';
    //p = "1*x + 2"_poly;
    std::cout << "1x + 2"_poly << '\n';
}