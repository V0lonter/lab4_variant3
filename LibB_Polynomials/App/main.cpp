#include <iostream>
#include "Polynomials.h"

static void print(const char* name, const double* c, int deg)
{
    std::cout << name << " = ";
    for (int i = 0; i <= deg; ++i)
    {
        std::cout << c[i] << (i < deg ? " " : "");
    }
    std::cout << " (degree " << deg << ")" << std::endl;
}

int main()
{
    double a[] = { 1.0, 2.0, 3.0 };
    double b[] = { 1.0, 1.0 };
    double out[8];
    int deg = 0;

    add(a, 2, b, 1, out, &deg);
    print("add", out, deg);
    multiply(a, 2, b, 1, out, &deg);
    print("multiply", out, deg);
    derivative(a, 2, out, &deg);
    print("derivative", out, deg);
    std::cout << "integral(0,1) = " << integral(a, 2, 0.0, 1.0) << std::endl;
    return 0;
}
