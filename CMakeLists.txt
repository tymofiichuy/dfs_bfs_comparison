cmake_minimum_required(VERSION 3.5)
project(traversal_algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${SOURCE_DIR})

add_executable(benchmark ${TEST_DIR}/benchmark.cpp ${SOURCE_DIR}/test_graph.cpp ${SOURCE_DIR}/traversal_algorithms.cpp)