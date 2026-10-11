#include <iostream>
#include <windows.h>

typedef void (*AddMulFunc)(const double*, int, const double*, int, double*, int*);
typedef void (*DerivFunc)(const double*, int, double*, int*);
typedef double (*IntegralFunc)(const double*, int, double, double);

static void printPoly(const double* p, int deg)
{
    if (deg < 0) { std::cout << "(invalid, deg=" << deg << ")"; return; }
    for (int i = deg; i >= 0; --i)
    {
        std::cout << p[i];
        if (i > 0) std::cout << "x^" << i << " + ";
    }
}

int main()
{
    std::cout << "=== Test A (Яроменко): явне зв'язування з Polynomials.dll ===" << std::endl;

    HMODULE hLib = LoadLibraryW(L"Polynomials.dll");
    if (!hLib)
    {
        std::cerr << "ERROR: не вдалося завантажити Polynomials.dll" << std::endl;
        return 1;
    }
    std::cout << "DLL завантажено успішно." << std::endl;

    auto add = reinterpret_cast<AddMulFunc>(GetProcAddress(hLib, "add"));
    auto multiply = reinterpret_cast<AddMulFunc>(GetProcAddress(hLib, "multiply"));
    auto derivative = reinterpret_cast<DerivFunc>(GetProcAddress(hLib, "derivative"));
    auto integral = reinterpret_cast<IntegralFunc>(GetProcAddress(hLib, "integral"));

    if (!add || !multiply || !derivative || !integral)
    {
        std::cerr << "ERROR: не всі функції знайдено в DLL" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "Усі 4 функції знайдено через GetProcAddress (ім'я не декороване завдяки extern \"C\")." << std::endl;

    double p1[] = { 1.0, 2.0, 3.0 };
    double p2[] = { -1.0, 1.0 };
    double result[8];
    int outDeg = 0;

    add(p1, 2, p2, 1, result, &outDeg);
    std::cout << "add: "; printPoly(result, outDeg); std::cout << std::endl;

    multiply(p1, 2, p2, 1, result, &outDeg);
    std::cout << "multiply: "; printPoly(result, outDeg); std::cout << std::endl;

    derivative(p1, 2, result, &outDeg);
    std::cout << "derivative: "; printPoly(result, outDeg); std::cout << std::endl;

    std::cout << "integral(p1,0,2) = " << integral(p1, 2, 0.0, 2.0) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;
    add(nullptr, 2, p2, 1, result, &outDeg);
    std::cout << "add(nullptr, ...): outDeg=" << outDeg << std::endl;
    std::cout << "integral(nullptr, -1, 0, 1) = " << integral(nullptr, -1, 0.0, 1.0) << std::endl;
    std::cout << "Аварійного завершення не відбулося." << std::endl;

    FreeLibrary(hLib);
    std::cout << std::endl << "DLL вивантажено." << std::endl;

    return 0;
}
