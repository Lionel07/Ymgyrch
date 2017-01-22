set (PROJECT_NAME YmgyrchQt)


project (${PROJECT_NAME})

set ( SOURCES
    main.cpp
    ROMInfo.cpp
    system_chooser.cpp
    sdl_subsys.cpp
    sdl_input.cpp
    UI/Debugger.cpp
    UI/MainWindow.cpp
    UI/Renderer.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIR})

if(WIN32)
    add_executable (${PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable (${PROJECT_NAME} ${SOURCES})
endif(WIN32)

qt5_use_modules(${PROJECT_NAME} Widgets)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

target_link_libraries (${PROJECT_NAME} libYmgyrch fmt)
