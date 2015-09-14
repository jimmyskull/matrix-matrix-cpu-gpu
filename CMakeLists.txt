cmake_minimum_required(VERSION 2.8.11)
project(MatrixMult)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -Wno-deprecated-declarations")

add_subdirectory(src)
