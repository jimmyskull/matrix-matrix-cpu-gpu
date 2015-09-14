cmake_minimum_required(VERSION 2.8.11)
project(MatrixMult)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules/)

add_subdirectory(src)
