cmake_minimum_required(VERSION 3.6)
project(3_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    3_4_no_stl.cpp)

add_executable(3_4 ${SOURCE_FILES})