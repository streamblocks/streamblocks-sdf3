cmake_minimum_required(VERSION 3.20)
project(streamblocks-sdf3)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(base)
add_subdirectory(sdf)

add_executable(sdf3 main.cpp)
