add_executable(InterpolationApp main.cpp)
target_link_libraries(InterpolationApp PRIVATE Interpolation)

if(BUILD_SHARED)
    add_custom_command(TARGET InterpolationApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:Interpolation>"
            "$<TARGET_FILE_DIR:InterpolationApp>"
    )
endif()
