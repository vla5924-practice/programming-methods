#include "TPolynomial.h"

int main()
{
    try
    {
        std::cout << "3.45*x 3 y 2 - 45*y^3*z^6*x^7 + 4.700"_poly << '\n';
        std::cout << "- zy^3*z^6*x^7*y^4 + 4.700 + x"_poly << '\n';
        /*TPolynomial p;
        p = p + 3;
        p = p + Monomial::make(2, 246);
        p = p + p;
        std::cout << p << '\n';*/
        std::cout << "xz + y"_poly << '\n';
    }
    catch (TPolynomial::SyntaxError & e)
    {
        std::cerr << e.what();
    }
}