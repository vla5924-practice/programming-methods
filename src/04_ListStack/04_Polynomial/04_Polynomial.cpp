#include "TPolynomial.h"

int main()
{
    TPolynomial p;
    p = p + Monomial::make(2, 2);
    p = p + "-3.15x^2"_monom;
    p = p + p + p;
    p.testcout();
}