#pragma once

#ifdef INTERPOLATION_STATIC
#define INTERP_API extern "C"
#elif defined(INTERPOLATION_EXPORTS)
#define INTERP_API extern "C" __declspec(dllexport)
#else
#define INTERP_API extern "C" __declspec(dllimport)
#endif

INTERP_API double lagrange(const double* xs, const double* ys, int n, double x);
INTERP_API double linearInterpolation(double x0, double y0, double x1, double y1, double x);
INTERP_API double interpolate(const double* xs, const double* ys, int n, double x);
INTERP_API double interpolationError(const double* xs, const double* ys, int n, double x, double trueValue);
