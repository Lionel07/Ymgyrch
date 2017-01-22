set ( SOURCES
    Gameboy.cpp
    LR35902.cpp
    LR35902_Instructions.cpp
)

add_library (sys_gb OBJECT ${SOURCES})
