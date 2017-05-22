FILE(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/tui/*.cxx)
FILE(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/includes/tui/*.hpp)

add_executable(YmgyrchTui ${SOURCES} ${HEADERS})
target_link_libraries (YmgyrchTui libYmgyrch fmt)

#cotire(YmgyrchTui)
