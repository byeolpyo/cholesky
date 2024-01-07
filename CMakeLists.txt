cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 11)
project(cholesky)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(cholesky src/cholesky.cpp src/compute.cpp src/table.cpp src/graph.cpp src/arch.cpp)
