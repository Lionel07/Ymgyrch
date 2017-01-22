
project(libYmgyrch)

set ( SOURCES
    config.cpp
    cpu.cpp
    device.cpp
    emucore.cpp
    input.cpp
    logger.cpp
)



add_library (libYmgyrch STATIC
    ${SOURCES}
    # $<TARGET_OBJECTS:cpu>
    $<TARGET_OBJECTS:memory>
    $<TARGET_OBJECTS:sys_chip8>
    $<TARGET_OBJECTS:sys_gb>
)


target_link_libraries (libYmgyrch fmt)

# add_subdirectory(cpu)
add_subdirectory(memory)
add_subdirectory(systems)
