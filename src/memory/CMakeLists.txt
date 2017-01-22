set ( SOURCES
    controller.cpp
    flat_ram.cpp
    mirror_ram.cpp
    null_memory.cpp
    rom.cpp
)

add_library (memory OBJECT ${SOURCES})
