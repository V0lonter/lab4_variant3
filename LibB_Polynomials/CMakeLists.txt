cmake_minimum_required(VERSION 3.20)
project(PolynomialsLibProject LANGUAGES CXX)

option(BUILD_SHARED "Build Polynomials as SHARED (DLL)" OFF)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(BUILD_SHARED)
    add_library(Polynomials SHARED src/Polynomials.cpp)
    target_compile_definitions(Polynomials PRIVATE POLYNOMIALS_EXPORTS)
else()
    add_library(Polynomials STATIC src/Polynomials.cpp)
    target_compile_definitions(Polynomials PUBLIC POLYNOMIALS_STATIC)
endif()

target_include_directories(Polynomials PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(Polynomials PUBLIC cxx_std_20)

add_subdirectory(App)
