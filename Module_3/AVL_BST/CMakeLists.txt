cmake_minimum_required(VERSION 3.6)
project(AVL_BST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        )

add_executable(AVL_BST ${SOURCE_FILES})