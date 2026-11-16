add_executable(PolynomialsApp main.cpp)
target_link_libraries(PolynomialsApp PRIVATE Polynomials)

if(BUILD_SHARED)
    add_custom_command(TARGET PolynomialsApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:Polynomials>"
            "$<TARGET_FILE_DIR:PolynomialsApp>"
    )
endif()
