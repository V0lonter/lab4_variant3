#pragma once

#ifdef POLYNOMIALS_STATIC
#define POLY_API extern "C"
#elif defined(POLYNOMIALS_EXPORTS)
#define POLY_API extern "C" __declspec(dllexport)
#else
#define POLY_API extern "C" __declspec(dllimport)
#endif

POLY_API void add(const double* a, int degA, const double* b, int degB, double* out, int* outDeg);
POLY_API void multiply(const double* a, int degA, const double* b, int degB, double* out, int* outDeg);
POLY_API void derivative(const double* a, int deg, double* out, int* outDeg);
POLY_API double integral(const double* a, int deg, double lower, double upper);
