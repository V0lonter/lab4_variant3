cmake_minimum_required(VERSION 3.20)
project(TestA_Explicit LANGUAGES CXX)

add_executable(TestA_Explicit main.cpp)
target_link_options(TestA_Explicit PRIVATE -static-libgcc -static-libstdc++ -static)

add_custom_command(TARGET TestA_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Polynomials.dll"
        "$<TARGET_FILE_DIR:TestA_Explicit>"
)
