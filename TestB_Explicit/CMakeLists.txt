cmake_minimum_required(VERSION 3.20)
project(TestB_Explicit LANGUAGES CXX)

add_executable(TestB_Explicit main.cpp)
target_link_options(TestB_Explicit PRIVATE -static-libgcc -static-libstdc++ -static)

add_custom_command(TARGET TestB_Explicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Interpolation.dll"
        "$<TARGET_FILE_DIR:TestB_Explicit>"
)
