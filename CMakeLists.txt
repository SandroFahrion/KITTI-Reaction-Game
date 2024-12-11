cmake_minimum_required(VERSION 3.10)
project(KITTIReactionGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "/MDd") # Dynamische Debug-Bibliothek
set(CMAKE_CXX_FLAGS_RELEASE "/MD") # Dynamische Release-Bibliothek


# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/bounding_box.cpp
    src/game_mode/game_mode.cpp
    src/game_mode/mode_1_direct_click.cpp
    src/game_mode/mode_2_color_change.cpp
    src/game_mode/mode_3_memory.cpp
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




# specify minimum version of cmake
cmake_minimum_required(VERSION 3.8)

# set the project name for tests
set(gameTest gameTest)
project(${gameTest} C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# list all test source files
set(TEST_SOURCES gameTest.cpp)

# include project's source directory and googletest headers
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# create executable for tests
add_executable(${gameTest} ${TEST_SOURCES})

# link googletest and project's static library to test executable
target_link_libraries(${gameTest} PUBLIC gtest_main ${projectName}_lib)

# add  test to the CMake testing framework
add_test(NAME ${gameTest} COMMAND ${gameTest})