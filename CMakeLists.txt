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
    helpers/debug/debug.cpp
    helpers/kitti_random.cpp
    helpers/time.cpp
    main.cpp
)

# Debugging option
option(ENABLE_DEBUG "Enable debugging" OFF)

if(ENABLE_DEBUG)
    add_definitions(-DDEBUG_MODE)
endif()

# Set OpenCV_DIR environment variable
set(OpenCV_DIR "C:/Users/User/Git/KITTI_Reaction_Game_workspace/OpenCV/build_opencv")

# Find OpenCV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(KITTIReactionGame ${SOURCES})

# Link OpenCV libraries
target_link_libraries(KITTIReactionGame ${OpenCV_LIBS})
