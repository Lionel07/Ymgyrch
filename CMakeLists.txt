cmake_minimum_required(VERSION 3.2.2)
project(Ymgyrch)

include_directories(${CMAKE_SOURCE_DIR}/src/includes)
include_directories(${CMAKE_SOURCE_DIR}/lib)

source_group(includes ${CMAKE_SOURCE_DIR}/src/includes/*)

add_subdirectory(lib)
add_subdirectory(src)

add_subdirectory(qt_gui)
add_subdirectory(tui)
