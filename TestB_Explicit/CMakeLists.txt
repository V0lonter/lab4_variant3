cmake_minimum_required(VERSION 3.20)
project(TestB_Explicit LANGUAGES CXX)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(TestB_Explicit main.cpp)
target_compile_features(TestB_Explicit PRIVATE cxx_std_20)

add_custom_command(TARGET TestB_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Interpolation.dll"
        "$<TARGET_FILE_DIR:TestB_Explicit>"
)
