add_executable(PolynomialsApp main.cpp)
target_link_libraries(PolynomialsApp PRIVATE Polynomials)
target_link_options(PolynomialsApp PRIVATE -static-libgcc -static-libstdc++ -static)
