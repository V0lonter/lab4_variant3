#define NOMINMAX
#include <windows.h>
#include <iostream>

typedef double (*LagrangeFunc)(const double*, const double*, int, double);
typedef double (*LinearFunc)(double, double, double, double, double);
typedef double (*InterpolateFunc)(const double*, const double*, int, double);
typedef double (*ErrorFunc)(const double*, const double*, int, double, double);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== Тест Б (Стасишін): явне зв'язування з Interpolation.dll ===" << std::endl;

    HMODULE lib = LoadLibraryW(L"Interpolation.dll");
    if (lib == nullptr)
    {
        std::cout << "ПОМИЛКА: не вдалося завантажити Interpolation.dll, код " << GetLastError() << std::endl;
        return 1;
    }
    std::cout << "Interpolation.dll завантажено." << std::endl;

    LagrangeFunc pLagrange = reinterpret_cast<LagrangeFunc>(GetProcAddress(lib, "lagrange"));
    LinearFunc pLinear = reinterpret_cast<LinearFunc>(GetProcAddress(lib, "linearInterpolation"));
    InterpolateFunc pInterpolate = reinterpret_cast<InterpolateFunc>(GetProcAddress(lib, "interpolate"));
    ErrorFunc pError = reinterpret_cast<ErrorFunc>(GetProcAddress(lib, "interpolationError"));

    int missing = (pLagrange == nullptr) + (pLinear == nullptr) + (pInterpolate == nullptr) + (pError == nullptr);
    if (missing > 0)
    {
        std::cout << "ПОМИЛКА: не всі функції знайдено в DLL" << std::endl;
        FreeLibrary(lib);
        return 1;
    }
    std::cout << "Усі 4 функції знайдено через GetProcAddress." << std::endl;

    double xs[] = { 0.0, 1.0, 2.0, 3.0 };
    double ys[] = { 1.0, 2.7183, 7.3891, 20.0855 };
    int n = 4;

    std::cout << "lagrange(x=1.5) = " << pLagrange(xs, ys, n, 1.5) << std::endl;
    std::cout << "linearInterpolation(x=0.5) = " << pLinear(0.0, 1.0, 1.0, 2.7183, 0.5) << std::endl;
    std::cout << "interpolate(x=1.5) = " << pInterpolate(xs, ys, n, 1.5) << std::endl;
    std::cout << "interpolationError(x=1.5, точне=4.4817) = " << pError(xs, ys, n, 1.5, 4.4817) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;
    std::cout << "lagrange(nullptr, ...) = " << pLagrange(nullptr, ys, n, 1.5) << " (очікується nan)" << std::endl;
    std::cout << "interpolate(n = 0) = " << pInterpolate(xs, ys, 0, 1.5) << " (очікується nan)" << std::endl;

    FARPROC missingFunc = GetProcAddress(lib, "noSuchFunction");
    std::cout << "GetProcAddress(\"noSuchFunction\") = " << (missingFunc == nullptr ? "nullptr" : "знайдено")
              << " (очікується nullptr)" << std::endl;

    FreeLibrary(lib);
    std::cout << std::endl << "DLL вивантажено, аварійного завершення не було." << std::endl;
    return 0;
}
