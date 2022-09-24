cmake_minimum_required(VERSION 3.2)
project(test)

set(PYBIND11_CPP_STANDARD -std=c++11)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)

add_library(disp_vector disp_vector.cpp)

pybind11_add_module(mymodule pymodule.cpp)

target_link_libraries(mymodule PRIVATE disp_vector)