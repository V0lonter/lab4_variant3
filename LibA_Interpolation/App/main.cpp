#include <iostream>
#include "Interpolation.h"

int main()
{
    double xs[] = { 0.0, 1.0, 2.0, 3.0 };
    double ys[] = { 1.0, 2.7183, 7.3891, 20.0855 };
    int n = 4;

    std::cout << "Lagrange interpolation at x=1.5: " << lagrange(xs, ys, n, 1.5) << std::endl;
    std::cout << "Linear interpolation (0,1)-(1,2.7183) at x=0.5: "
        << linearInterpolation(0.0, 1.0, 1.0, 2.7183, 0.5) << std::endl;
    std::cout << "Piecewise interpolate at x=1.5: " << interpolate(xs, ys, n, 1.5) << std::endl;
    std::cout << "Interpolation error at x=1.5 (true=e^1.5=4.4817): "
        << interpolationError(xs, ys, n, 1.5, 4.4817) << std::endl;

    return 0;
}
