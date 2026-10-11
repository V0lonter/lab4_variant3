#include "Interpolation.h"
#include <cmath>

double lagrange(const double* xs, const double* ys, int n, double x)
{
    if (xs == nullptr || ys == nullptr || n <= 0)
        return std::nan("");

    double result = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double term = ys[i];
        for (int j = 0; j < n; ++j)
        {
            if (j == i)
                continue;
            double denom = xs[i] - xs[j];
            if (denom == 0.0)
                return std::nan("");
            term *= (x - xs[j]) / denom;
        }
        result += term;
    }
    return result;
}

double linearInterpolation(double x0, double y0, double x1, double y1, double x)
{
    if (x1 == x0)
        return std::nan("");
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}

double interpolate(const double* xs, const double* ys, int n, double x)
{
    if (xs == nullptr || ys == nullptr || n <= 0)
        return std::nan("");
    if (n == 1)
        return ys[0];

    if (x <= xs[0])
        return linearInterpolation(xs[0], ys[0], xs[1], ys[1], x);
    if (x >= xs[n - 1])
        return linearInterpolation(xs[n - 2], ys[n - 2], xs[n - 1], ys[n - 1], x);

    for (int i = 0; i < n - 1; ++i)
    {
        if (x >= xs[i] && x <= xs[i + 1])
            return linearInterpolation(xs[i], ys[i], xs[i + 1], ys[i + 1], x);
    }
    return std::nan("");
}

double interpolationError(const double* xs, const double* ys, int n, double x, double trueValue)
{
    double approx = lagrange(xs, ys, n, x);
    if (std::isnan(approx))
        return std::nan("");
    return std::fabs(trueValue - approx);
}
