# Test base
add_executable(test_base test_base.cpp)
target_link_libraries(test_base PRIVATE matrix_lib)
add_test(NAME BaseTest COMMAND test_base)

# Main per debug
add_executable(main main.cpp)
target_link_libraries(main PRIVATE matrix_lib)