cmake_minimum_required(VERSION 3.19)
project(py_string)

set(CMAKE_CXX_STANDARD 14)

add_library(py_string INTERFACE py_string.h)
add_library(doctest INTERFACE doctest.h)

add_executable(py_string_tests tests.cpp)
target_link_libraries(py_string_tests PUBLIC py_string doctest)
