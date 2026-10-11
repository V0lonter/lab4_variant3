#include <iostream>
#include <windows.h>

typedef double (*LagrangeFunc)(const double*, const double*, int, double);
typedef double (*LinearFunc)(double, double, double, double, double);
typedef double (*InterpolateFunc)(const double*, const double*, int, double);
typedef double (*ErrorFunc)(const double*, const double*, int, double, double);

int main()
{
    std::cout << "=== Test B (Стасишін): явне зв'язування з Interpolation.dll ===" << std::endl;

    HMODULE hLib = LoadLibraryW(L"Interpolation.dll");
    if (!hLib)
    {
        std::cerr << "ERROR: не вдалося завантажити Interpolation.dll" << std::endl;
        return 1;
    }
    std::cout << "DLL завантажено успішно." << std::endl;

    auto lagrange = reinterpret_cast<LagrangeFunc>(GetProcAddress(hLib, "lagrange"));
    auto linearInterpolation = reinterpret_cast<LinearFunc>(GetProcAddress(hLib, "linearInterpolation"));
    auto interpolate = reinterpret_cast<InterpolateFunc>(GetProcAddress(hLib, "interpolate"));
    auto interpolationError = reinterpret_cast<ErrorFunc>(GetProcAddress(hLib, "interpolationError"));

    if (!lagrange || !linearInterpolation || !interpolate || !interpolationError)
    {
        std::cerr << "ERROR: не всі функції знайдено в DLL" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "Усі 4 функції знайдено через GetProcAddress." << std::endl;

    double xs[] = { 0.0, 1.0, 2.0, 3.0 };
    double ys[] = { 1.0, 2.7183, 7.3891, 20.0855 };
    int n = 4;

    std::cout << "lagrange(x=1.5) = " << lagrange(xs, ys, n, 1.5) << std::endl;
    std::cout << "linearInterpolation(x=0.5) = " << linearInterpolation(0.0, 1.0, 1.0, 2.7183, 0.5) << std::endl;
    std::cout << "interpolate(x=1.5) = " << interpolate(xs, ys, n, 1.5) << std::endl;
    std::cout << "interpolationError(x=1.5) = " << interpolationError(xs, ys, n, 1.5, 4.4817) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;
    std::cout << "lagrange(nullptr, ...) = " << lagrange(nullptr, ys, n, 1.5) << std::endl;
    std::cout << "lagrange(n=0) = " << lagrange(xs, ys, 0, 1.5) << std::endl;
    std::cout << "Аварійного завершення не відбулося." << std::endl;

    FreeLibrary(hLib);
    std::cout << std::endl << "DLL вивантажено." << std::endl;

    return 0;
}
