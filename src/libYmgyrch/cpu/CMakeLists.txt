FILE(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/libYmgyrch/cpu/*.cxx)
FILE(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/includes/ymgyrch/cpu/*.hpp)

add_library(libCpu OBJECT
    ${SOURCES}
    ${HEADERS}
)
