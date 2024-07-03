cmake_minimum_required(VERSION 3.10)
project(KITTIReactionGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/bounding_box.cpp
    src/game_mode/game_mode.cpp
    src/game_mode/mode_1_direct_click.cpp
    src/game_mode/mode_2_color_change.cpp
    src/gui.cpp
    src/image.cpp
    src/kitti_dataset.cpp
    src/player.cpp
    src/reaction_game.cpp
    src/debug.cpp
    main.cpp
)

# Debugging option
option(ENABLE_DEBUG "Enable debugging" OFF)

if(ENABLE_DEBUG)
    add_definitions(-DDEBUG_MODE)
endif()

# Find OpenCV package
#find_package(OpenCV REQUIRED)
#include_directories(../opencv/cmake/OpenCVMinDepVersions.cmake)

# Add executable
add_executable(KITTIReactionGame ${SOURCES})

# Link OpenCV libraries
#target_link_libraries(KittiReactionGame ${OpenCV_LIBS})
