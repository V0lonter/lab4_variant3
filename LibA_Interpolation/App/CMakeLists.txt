add_executable(InterpolationApp main.cpp)
target_link_libraries(InterpolationApp PRIVATE Interpolation)
target_link_options(InterpolationApp PRIVATE -static-libgcc -static-libstdc++ -static)
