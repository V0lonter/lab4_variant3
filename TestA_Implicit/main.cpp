#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "Polynomials.h"

static void print(const char* name, const double* c, int deg)
{
    std::cout << name << " = ";
    for (int i = 0; i <= deg; ++i)
    {
        std::cout << c[i] << (i < deg ? " " : "");
    }
    std::cout << " (степінь " << deg << ")" << std::endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== Тест А (Яроменко): неявне зв'язування з Polynomials.dll ===" << std::endl;

    double a[] = { 1.0, 2.0, 3.0 };
    double b[] = { 1.0, 1.0 };
    double out[8];
    int deg = 0;

    add(a, 2, b, 1, out, &deg);
    print("add(1+2x+3x^2, 1+x)", out, deg);
    multiply(a, 2, b, 1, out, &deg);
    print("multiply(1+2x+3x^2, 1+x)", out, deg);
    derivative(a, 2, out, &deg);
    print("derivative(1+2x+3x^2)", out, deg);
    std::cout << "integral(1+2x+3x^2, 0..1) = " << integral(a, 2, 0.0, 1.0) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;

    deg = 0;
    add(nullptr, 2, b, 1, out, &deg);
    std::cout << "add(nullptr, ...): outDeg = " << deg << " (очікується -1)" << std::endl;

    deg = 0;
    multiply(a, -1, b, 1, out, &deg);
    std::cout << "multiply(degA = -1): outDeg = " << deg << " (очікується -1)" << std::endl;

    double c[] = { 5.0 };
    derivative(c, 0, out, &deg);
    print("derivative(стала 5)", out, deg);

    std::cout << "integral(nullptr, ...) = " << integral(nullptr, 2, 0.0, 1.0) << " (очікується nan)" << std::endl;
    std::cout << "integral(межі 1..0) = " << integral(a, 2, 1.0, 0.0) << " (очікується -3)" << std::endl;

    std::vector<double> big(200, 1.0);
    std::vector<double> bigOut(399, 0.0);
    deg = 0;
    multiply(big.data(), 199, big.data(), 199, bigOut.data(), &deg);
    std::cout << "multiply(степінь 199 x 199): outDeg = " << deg << ", старший коефіцієнт = " << bigOut[398]
              << ", середній коефіцієнт = " << bigOut[199] << std::endl;

    std::cout << std::endl << "Усі граничні випадки оброблено без аварійного завершення програми." << std::endl;
    return 0;
}
