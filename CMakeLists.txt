cmake_minimum_required(VERSION 3.28)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2 main.cpp
        tests/run_all_tests.cpp
        tests/test_utils.cpp
        tests/test_complex.cpp
        tests/test_vector.cpp
        tests/test_result_info.cpp
        tests/run_test_matrix.cpp
        tests/run_test_square_matrix.cpp
)
