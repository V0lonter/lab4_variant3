cmake_minimum_required(VERSION 3.20)
project(TestA_Implicit LANGUAGES CXX)

add_executable(TestA_Implicit main.cpp)

target_include_directories(TestA_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Polynomials/include
)

target_link_libraries(TestA_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Polynomials/lib/Polynomials.lib
)

target_link_options(TestA_Implicit PRIVATE -static-libgcc -static-libstdc++ -static)

add_custom_command(TARGET TestA_Implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Polynomials/bin/Polynomials.dll"
        "$<TARGET_FILE_DIR:TestA_Implicit>"
)
