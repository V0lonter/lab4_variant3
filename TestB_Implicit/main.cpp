#include <iostream>
#include <cmath>
#include "Interpolation.h"

int main()
{
    std::cout << "=== Test B (Стасишін): неявне зв'язування з Interpolation.dll ===" << std::endl;

    double xs[] = { 0.0, 1.0, 2.0, 3.0 };
    double ys[] = { 1.0, 2.7183, 7.3891, 20.0855 };
    int n = 4;

    std::cout << "lagrange(x=1.5) = " << lagrange(xs, ys, n, 1.5) << std::endl;
    std::cout << "linearInterpolation((0,1)-(1,2.7183), x=0.5) = "
        << linearInterpolation(0.0, 1.0, 1.0, 2.7183, 0.5) << std::endl;
    std::cout << "interpolate(x=1.5) = " << interpolate(xs, ys, n, 1.5) << std::endl;
    std::cout << "interpolationError(x=1.5, true=4.4817) = "
        << interpolationError(xs, ys, n, 1.5, 4.4817) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;

    double r1 = lagrange(nullptr, ys, n, 1.5);
    std::cout << "lagrange(nullptr, ...) = " << r1 << " (очікується nan)" << std::endl;

    double r2 = lagrange(xs, ys, 0, 1.5);
    std::cout << "lagrange(n=0) = " << r2 << " (очікується nan)" << std::endl;

    double r3 = linearInterpolation(5.0, 1.0, 5.0, 2.0, 5.0);
    std::cout << "linearInterpolation(x0==x1) = " << r3 << " (очікується nan)" << std::endl;

    double xsDup[] = { 1.0, 1.0 };
    double ysDup[] = { 2.0, 3.0 };
    double r4 = lagrange(xsDup, ysDup, 2, 1.0);
    std::cout << "lagrange(повторювані xs) = " << r4 << " (очікується nan)" << std::endl;

    double r5 = interpolate(xs, ys, n, 100.0);
    std::cout << "interpolate(x далеко поза межами) = " << r5
        << " (екстраполяція по крайньому відрізку, без аварії)" << std::endl;

    double bigXs[500];
    double bigYs[500];
    for (int i = 0; i < 500; ++i) { bigXs[i] = i; bigYs[i] = i * i; }
    double r6 = interpolate(bigXs, bigYs, 500, 250.5);
    std::cout << "interpolate(500 вузлів) = " << r6 << " (без переповнення/аварії)" << std::endl;

    std::cout << std::endl << "Усі граничні випадки оброблено без аварійного завершення програми." << std::endl;

    return 0;
}
