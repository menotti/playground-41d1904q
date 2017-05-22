cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_FLAGS "-ftree-vectorize -fopt-info-vec-optimized")
add_executable(autovector autovector.cpp)