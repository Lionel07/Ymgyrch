set ( SOURCES
    CHIP8.cpp
    CHIP8Cpu.cpp
    Chip8GPU.cpp
)

add_library (sys_chip8 OBJECT ${SOURCES})
