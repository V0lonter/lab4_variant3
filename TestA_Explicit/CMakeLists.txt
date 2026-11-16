cmake_minimum_required(VERSION 3.20)
project(TestA_Explicit LANGUAGES CXX)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(TestA_Explicit main.cpp)
target_compile_features(TestA_Explicit PRIVATE cxx_std_20)

add_custom_command(TARGET TestA_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Polynomials.dll"
        "$<TARGET_FILE_DIR:TestA_Explicit>"
)
