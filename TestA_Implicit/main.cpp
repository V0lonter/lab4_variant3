#include <iostream>
#include <cmath>
#include "Polynomials.h"

static void printPoly(const double* p, int deg)
{
    if (deg < 0) { std::cout << "(invalid, deg=" << deg << ")"; return; }
    for (int i = deg; i >= 0; --i)
    {
        std::cout << p[i];
        if (i > 0) std::cout << "x^" << i << " + ";
    }
}

int main()
{
    std::cout << "=== Test A (Яроменко): неявне зв'язування з Polynomials.dll ===" << std::endl;

    double p1[] = { 1.0, 2.0, 3.0 };   // 3x^2 + 2x + 1
    double p2[] = { -1.0, 1.0 };       // x - 1
    double result[8];
    int outDeg = 0;

    add(p1, 2, p2, 1, result, &outDeg);
    std::cout << "add: "; printPoly(result, outDeg); std::cout << std::endl;

    multiply(p1, 2, p2, 1, result, &outDeg);
    std::cout << "multiply: "; printPoly(result, outDeg); std::cout << std::endl;

    derivative(p1, 2, result, &outDeg);
    std::cout << "derivative: "; printPoly(result, outDeg); std::cout << std::endl;

    std::cout << "integral(p1,0,2) = " << integral(p1, 2, 0.0, 2.0) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;

    add(nullptr, 2, p2, 1, result, &outDeg);
    std::cout << "add(nullptr, ...): outDeg=" << outDeg << " (очікується -1, без аварійного завершення)" << std::endl;

    add(p1, -1, p2, 1, result, &outDeg);
    std::cout << "add(deg1=-1, ...): outDeg=" << outDeg << " (очікується -1)" << std::endl;

    double zeroDeg[] = { 5.0 };
    derivative(zeroDeg, 0, result, &outDeg);
    std::cout << "derivative(константа 5): outDeg=" << outDeg << ", result[0]=" << result[0]
        << " (очікується 0, 0)" << std::endl;

    double big1[200];
    double big2[200];
    for (int i = 0; i < 200; ++i) { big1[i] = 1.0; big2[i] = 1.0; }
    double bigResult[400];
    multiply(big1, 199, big2, 199, bigResult, &outDeg);
    std::cout << "multiply(два поліноми степеня 199): outDeg=" << outDeg
        << " (очікується 398, без переповнення/аварії)" << std::endl;

    std::cout << "integral(nullptr, -1, 0, 1) = " << integral(nullptr, -1, 0.0, 1.0)
        << " (очікується nan)" << std::endl;

    std::cout << std::endl << "Усі граничні випадки оброблено без аварійного завершення програми." << std::endl;

    return 0;
}
