FILE(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/libYmgyrch/system/*.cxx)
FILE(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/includes/ymgyrch/systems/*.hpp)

add_library(libSys OBJECT
    ${SOURCES}
    ${HEADERS}
)
