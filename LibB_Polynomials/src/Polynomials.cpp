#include "Polynomials.h"
#include <climits>
#include <cmath>
#include <limits>

static void fail(int* outDeg)
{
    if (outDeg != nullptr)
    {
        *outDeg = -1;
    }
}

void add(const double* a, int degA, const double* b, int degB, double* out, int* outDeg)
{
    int bad = (a == nullptr) + (b == nullptr) + (out == nullptr) + (outDeg == nullptr) + (degA < 0) + (degB < 0);
    if (bad > 0)
    {
        fail(outDeg);
        return;
    }
    int deg = degA > degB ? degA : degB;
    for (int i = 0; i <= deg; ++i)
    {
        double va = i <= degA ? a[i] : 0.0;
        double vb = i <= degB ? b[i] : 0.0;
        out[i] = va + vb;
    }
    *outDeg = deg;
}

void multiply(const double* a, int degA, const double* b, int degB, double* out, int* outDeg)
{
    int bad = (a == nullptr) + (b == nullptr) + (out == nullptr) + (outDeg == nullptr) + (degA < 0) + (degB < 0);
    if (bad > 0)
    {
        fail(outDeg);
        return;
    }
    long long total = static_cast<long long>(degA) + degB;
    if (total >= INT_MAX)
    {
        fail(outDeg);
        return;
    }
    int deg = static_cast<int>(total);
    for (int i = 0; i <= deg; ++i)
    {
        out[i] = 0.0;
    }
    for (int i = 0; i <= degA; ++i)
    {
        for (int j = 0; j <= degB; ++j)
        {
            out[i + j] += a[i] * b[j];
        }
    }
    *outDeg = deg;
}

void derivative(const double* a, int deg, double* out, int* outDeg)
{
    int bad = (a == nullptr) + (out == nullptr) + (outDeg == nullptr) + (deg < 0);
    if (bad > 0)
    {
        fail(outDeg);
        return;
    }
    if (deg == 0)
    {
        out[0] = 0.0;
        *outDeg = 0;
        return;
    }
    for (int i = 1; i <= deg; ++i)
    {
        out[i - 1] = i * a[i];
    }
    *outDeg = deg - 1;
}

double integral(const double* a, int deg, double lower, double upper)
{
    int bad = (a == nullptr) + (deg < 0) + std::isnan(lower) + std::isnan(upper);
    if (bad > 0)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double result = 0.0;
    double powLower = lower;
    double powUpper = upper;
    for (int i = 0; i <= deg; ++i)
    {
        result += a[i] * (powUpper - powLower) / (i + 1);
        powLower *= lower;
        powUpper *= upper;
    }
    return result;
}
