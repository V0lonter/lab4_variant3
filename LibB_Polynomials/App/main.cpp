#include <iostream>
#include "Polynomials.h"

static void printPoly(const double* p, int deg)
{
    for (int i = deg; i >= 0; --i)
    {
        std::cout << p[i];
        if (i > 0)
            std::cout << "x^" << i << " + ";
    }
    std::cout << std::endl;
}

int main()
{
    double p1[] = { 1.0, 2.0, 3.0 };   // 3x^2 + 2x + 1
    double p2[] = { -1.0, 1.0 };       // x - 1
    double result[8];
    int outDeg = 0;

    add(p1, 2, p2, 1, result, &outDeg);
    std::cout << "p1 + p2 (deg=" << outDeg << "): ";
    printPoly(result, outDeg);

    multiply(p1, 2, p2, 1, result, &outDeg);
    std::cout << "p1 * p2 (deg=" << outDeg << "): ";
    printPoly(result, outDeg);

    derivative(p1, 2, result, &outDeg);
    std::cout << "d(p1)/dx (deg=" << outDeg << "): ";
    printPoly(result, outDeg);

    double integ = integral(p1, 2, 0.0, 2.0);
    std::cout << "integral(p1, 0, 2) = " << integ << std::endl;

    return 0;
}
