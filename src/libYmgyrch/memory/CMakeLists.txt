FILE(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/libYmgyrch/memory/*.cxx)
FILE(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/includes/ymgyrch/memory/*.hpp)

add_library(libMem OBJECT
    ${SOURCES}
    ${HEADERS}
)
