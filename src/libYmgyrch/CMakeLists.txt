project(libYmgyrch)
FILE(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/libYmgyrch/*.cxx)
FILE(GLOB HEADERS ${CMAKE_SOURCE_DIR}/src/includes/ymgyrch/*.hpp)


add_library(libYmgyrch STATIC
    ${SOURCES}
    ${HEADERS}
    $<TARGET_OBJECTS:libMem>
    $<TARGET_OBJECTS:libCpu>
    $<TARGET_OBJECTS:libSys>
)

target_link_libraries (libYmgyrch fmt)
add_subdirectory(memory)
add_subdirectory(cpu)
add_subdirectory(system)
#cotire(libYmgyrch)
