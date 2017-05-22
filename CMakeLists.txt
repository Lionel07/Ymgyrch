# Project / CMake setup
cmake_minimum_required(VERSION 3.2.2)
project(Ymgyrch)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
include(cotire/CMake/cotire)

# Includes
include_directories(${CMAKE_SOURCE_DIR}/src/includes)
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Compilation units
add_subdirectory(lib)
add_subdirectory(src)
