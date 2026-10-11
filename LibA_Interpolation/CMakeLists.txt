cmake_minimum_required(VERSION 3.20)
project(InterpolationLibProject LANGUAGES CXX)

option(BUILD_SHARED "Build Interpolation as SHARED (DLL) instead of STATIC" OFF)

if(BUILD_SHARED)
    add_library(Interpolation SHARED src/Interpolation.cpp)
    target_compile_definitions(Interpolation PRIVATE INTERPOLATION_EXPORTS)
    set_target_properties(Interpolation PROPERTIES
        PREFIX ""
        IMPORT_PREFIX ""
        IMPORT_SUFFIX ".lib"
    )
else()
    add_library(Interpolation STATIC src/Interpolation.cpp)
    target_compile_definitions(Interpolation PUBLIC INTERPOLATION_STATIC)
endif()

target_include_directories(Interpolation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(Interpolation PUBLIC cxx_std_20)

add_subdirectory(App)
