#define NOMINMAX
#include <windows.h>
#include <iostream>

typedef void (*AddMulFunc)(const double*, int, const double*, int, double*, int*);
typedef void (*DerivFunc)(const double*, int, double*, int*);
typedef double (*IntegralFunc)(const double*, int, double, double);

static void print(const char* name, const double* c, int deg)
{
    std::cout << name << " = ";
    for (int i = 0; i <= deg; ++i)
    {
        std::cout << c[i] << (i < deg ? " " : "");
    }
    std::cout << " (степінь " << deg << ")" << std::endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== Тест А (Яроменко): явне зв'язування з Polynomials.dll ===" << std::endl;

    HMODULE lib = LoadLibraryW(L"Polynomials.dll");
    if (lib == nullptr)
    {
        std::cout << "ПОМИЛКА: не вдалося завантажити Polynomials.dll, код " << GetLastError() << std::endl;
        return 1;
    }
    std::cout << "Polynomials.dll завантажено." << std::endl;

    AddMulFunc pAdd = reinterpret_cast<AddMulFunc>(GetProcAddress(lib, "add"));
    AddMulFunc pMultiply = reinterpret_cast<AddMulFunc>(GetProcAddress(lib, "multiply"));
    DerivFunc pDerivative = reinterpret_cast<DerivFunc>(GetProcAddress(lib, "derivative"));
    IntegralFunc pIntegral = reinterpret_cast<IntegralFunc>(GetProcAddress(lib, "integral"));

    int missing = (pAdd == nullptr) + (pMultiply == nullptr) + (pDerivative == nullptr) + (pIntegral == nullptr);
    if (missing > 0)
    {
        std::cout << "ПОМИЛКА: не всі функції знайдено в DLL" << std::endl;
        FreeLibrary(lib);
        return 1;
    }
    std::cout << "Усі 4 функції знайдено через GetProcAddress." << std::endl;

    double a[] = { 1.0, 2.0, 3.0 };
    double b[] = { 1.0, 1.0 };
    double out[8];
    int deg = 0;

    pAdd(a, 2, b, 1, out, &deg);
    print("add(1+2x+3x^2, 1+x)", out, deg);
    pMultiply(a, 2, b, 1, out, &deg);
    print("multiply(1+2x+3x^2, 1+x)", out, deg);
    pDerivative(a, 2, out, &deg);
    print("derivative(1+2x+3x^2)", out, deg);
    std::cout << "integral(1+2x+3x^2, 0..1) = " << pIntegral(a, 2, 0.0, 1.0) << std::endl;

    std::cout << std::endl << "--- Граничні випадки ---" << std::endl;

    deg = 0;
    pAdd(nullptr, 2, b, 1, out, &deg);
    std::cout << "add(nullptr, ...): outDeg = " << deg << " (очікується -1)" << std::endl;

    FARPROC missingFunc = GetProcAddress(lib, "noSuchFunction");
    std::cout << "GetProcAddress(\"noSuchFunction\") = " << (missingFunc == nullptr ? "nullptr" : "знайдено")
              << " (очікується nullptr)" << std::endl;

    FreeLibrary(lib);
    std::cout << std::endl << "DLL вивантажено, аварійного завершення не було." << std::endl;
    return 0;
}
