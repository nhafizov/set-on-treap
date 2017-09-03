cmake_minimum_required(VERSION 3.6)
project(hse_summer_2017)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp my_set.h test.h test.cpp treap.h timer.h)
add_executable(hse_summer_2017 ${SOURCE_FILES})