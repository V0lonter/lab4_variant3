#include "Polynomials.h"
#include <algorithm>
#include <cmath>

void add(const double* p1, int deg1, const double* p2, int deg2, double* result, int* outDeg)
{
    if (p1 == nullptr || p2 == nullptr || result == nullptr || outDeg == nullptr || deg1 < 0 || deg2 < 0)
    {
        if (outDeg != nullptr)
            *outDeg = -1;
        return;
    }

    int maxDeg = std::max(deg1, deg2);
    for (int i = 0; i <= maxDeg; ++i)
    {
        double a = (i <= deg1) ? p1[i] : 0.0;
        double b = (i <= deg2) ? p2[i] : 0.0;
        result[i] = a + b;
    }

    int actualDeg = maxDeg;
    while (actualDeg > 0 && result[actualDeg] == 0.0)
        --actualDeg;

    *outDeg = actualDeg;
}

void multiply(const double* p1, int deg1, const double* p2, int deg2, double* result, int* outDeg)
{
    if (p1 == nullptr || p2 == nullptr || result == nullptr || outDeg == nullptr || deg1 < 0 || deg2 < 0)
    {
        if (outDeg != nullptr)
            *outDeg = -1;
        return;
    }

    int resultDeg = deg1 + deg2;
    for (int i = 0; i <= resultDeg; ++i)
        result[i] = 0.0;

    for (int i = 0; i <= deg1; ++i)
    {
        for (int j = 0; j <= deg2; ++j)
            result[i + j] += p1[i] * p2[j];
    }

    while (resultDeg > 0 && result[resultDeg] == 0.0)
        --resultDeg;

    *outDeg = resultDeg;
}

void derivative(const double* p, int deg, double* result, int* outDeg)
{
    if (p == nullptr || result == nullptr || outDeg == nullptr || deg < 0)
    {
        if (outDeg != nullptr)
            *outDeg = -1;
        return;
    }

    if (deg == 0)
    {
        result[0] = 0.0;
        *outDeg = 0;
        return;
    }

    for (int i = 1; i <= deg; ++i)
        result[i - 1] = p[i] * static_cast<double>(i);

    *outDeg = deg - 1;
}

double integral(const double* p, int deg, double a, double b)
{
    if (p == nullptr || deg < 0)
        return std::nan("");

    double sumA = 0.0;
    double sumB = 0.0;
    for (int i = 0; i <= deg; ++i)
    {
        double coeff = p[i] / static_cast<double>(i + 1);
        sumA += coeff * std::pow(a, i + 1);
        sumB += coeff * std::pow(b, i + 1);
    }
    return sumB - sumA;
}
