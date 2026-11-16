#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <vector>
#include "Interpolation.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== Тест Б (Стасишін): неявне зв'язування з Interpolation.dll ===" << std::endl;

    double xs[] = { 0.0, 1.0, 2.0, 3.0 };
    double ys[] = { 1.0, 2.7183, 7.3891, 20.0855 };
    int n = 4;

    std::cout << "lagrange(x=1.5) = " << lagrange(xs, ys, n, 1.5) << std::endl;
    std::cout << "linearInterpolation((0;1)-(1;2.7183), x=0.5) = " << linearInterpolation(0.0, 1.0, 1.0, 2.7183, 0.5) << std::endl;
    std::cout << "interpolate(x=1.5) = " << interpolate(xs, ys, n, 1.5) << std::endl;
    std::cout << "interpolationError(x=1.5, точне=4.4817) = " << interpolationError(xs, ys, n, 1.5, 4.4817) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;

    std::cout << "lagrange(nullptr, ...) = " << lagrange(nullptr, ys, n, 1.5) << " (очікується nan)" << std::endl;
    std::cout << "lagrange(n = 0) = " << lagrange(xs, ys, 0, 1.5) << " (очікується nan)" << std::endl;
    std::cout << "linearInterpolation(x0 = x1) = " << linearInterpolation(5.0, 1.0, 5.0, 2.0, 5.0) << " (очікується nan)" << std::endl;

    double xsDup[] = { 1.0, 1.0 };
    double ysDup[] = { 2.0, 3.0 };
    std::cout << "lagrange(повторювані вузли) = " << lagrange(xsDup, ysDup, 2, 1.0) << " (очікується nan)" << std::endl;

    std::cout << "interpolate(x = 100, далеко поза межами) = " << interpolate(xs, ys, n, 100.0)
              << " (екстраполяція крайнім відрізком)" << std::endl;

    std::vector<double> bigX(500);
    std::vector<double> bigY(500);
    for (int i = 0; i < 500; ++i)
    {
        bigX[i] = i;
        bigY[i] = static_cast<double>(i) * i;
    }
    std::cout << "interpolate(500 вузлів, x = 250.5) = " << interpolate(bigX.data(), bigY.data(), 500, 250.5)
              << " (очікується 62750.5)" << std::endl;

    std::cout << std::endl << "Усі граничні випадки оброблено без аварійного завершення програми." << std::endl;
    return 0;
}
