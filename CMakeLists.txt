# Project / CMake setup
cmake_minimum_required(VERSION 3.2.2)
project(Ymgyrch)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
include(cotire/CMake/cotire)

# Configure compiler
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")



set(LINK_FLAGS "/LTCG ")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS} /GENPROFILE")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")
#set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${LINK_FLAGS}")
# Includes
include_directories(${CMAKE_SOURCE_DIR}/src/includes)
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Compilation units
add_subdirectory(lib)
add_subdirectory(src)
