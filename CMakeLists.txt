cmake_minimum_required(VERSION 3.26)
project(MidProject)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenMP REQUIRED)

add_executable(MidProject main.cpp
        Sequential.cpp
        Sequential.h
        Parallel.cpp
        Parallel.h)
target_link_libraries(MidProject OpenMP::OpenMP_CXX)