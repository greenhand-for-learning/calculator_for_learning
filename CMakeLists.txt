cmake_minimum_required(VERSION 3.15)
project(CASIO)

set(CMAKE_CXX_STANDARD 11)

add_executable(CASIO main.cpp calculate.h calculate.cpp complex.h complex.cpp "statistic.cpp" statistic.h radix.cpp radix.h)