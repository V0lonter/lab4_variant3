#include "Interpolation.h"
#include <cmath>
#include <limits>

static double nanValue()
{
    return std::numeric_limits<double>::quiet_NaN();
}

double lagrange(const double* xs, const double* ys, int n, double x)
{
    if (xs == nullptr || ys == nullptr || n <= 0 || std::isnan(x))
    {
        return nanValue();
    }
    double result = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double term = ys[i];
        for (int j = 0; j < n; ++j)
        {
            if (j == i)
            {
                continue;
            }
            double denom = xs[i] - xs[j];
            if (denom == 0.0)
            {
                return nanValue();
            }
            term *= (x - xs[j]) / denom;
        }
        result += term;
    }
    return result;
}

double linearInterpolation(double x0, double y0, double x1, double y1, double x)
{
    if (x1 == x0)
    {
        return nanValue();
    }
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}

double interpolate(const double* xs, const double* ys, int n, double x)
{
    if (xs == nullptr || ys == nullptr || n <= 0 || std::isnan(x))
    {
        return nanValue();
    }
    if (n == 1)
    {
        return ys[0];
    }
    int i = 0;
    while (i < n - 2 && x > xs[i + 1])
    {
        ++i;
    }
    return linearInterpolation(xs[i], ys[i], xs[i + 1], ys[i + 1], x);
}

double interpolationError(const double* xs, const double* ys, int n, double x, double trueValue)
{
    double approx = lagrange(xs, ys, n, x);
    return std::fabs(trueValue - approx);
}
