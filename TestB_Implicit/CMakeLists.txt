cmake_minimum_required(VERSION 3.20)
project(TestB_Implicit LANGUAGES CXX)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(TestB_Implicit main.cpp)
target_compile_features(TestB_Implicit PRIVATE cxx_std_20)

target_include_directories(TestB_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Interpolation/include
)

target_link_libraries(TestB_Implicit PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Interpolation/lib/Interpolation.lib
)

add_custom_command(TARGET TestB_Implicit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Interpolation/bin/Interpolation.dll"
        "$<TARGET_FILE_DIR:TestB_Implicit>"
)
