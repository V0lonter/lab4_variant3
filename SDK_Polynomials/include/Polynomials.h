#pragma once

#ifdef POLYNOMIALS_STATIC
#define POLY_API extern "C"
#elif defined(POLYNOMIALS_EXPORTS)
#define POLY_API extern "C" __declspec(dllexport)
#else
#define POLY_API extern "C" __declspec(dllimport)
#endif

// Поліном задається масивом коефіцієнтів coeffs[0..deg], де coeffs[i] -
// коефіцієнт при x^i (deg - старший степінь, довжина масиву = deg+1).
// Масиви result мають бути заздалегідь виділені викликачем розміром
// не менше (max(deg1,deg2)+1) елементів для add/multiply та deg елементів
// для derivative. Фактичний результуючий степінь повертається через outDeg.

POLY_API void add(const double* p1, int deg1, const double* p2, int deg2, double* result, int* outDeg);
POLY_API void multiply(const double* p1, int deg1, const double* p2, int deg2, double* result, int* outDeg);
POLY_API void derivative(const double* p, int deg, double* result, int* outDeg);
POLY_API double integral(const double* p, int deg, double a, double b);
