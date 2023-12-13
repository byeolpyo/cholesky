cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 11)
project(cholesky)

add_executable(cholesky src/cholesky.cpp src/compute.cpp src/table.cpp src/graph.cpp)
