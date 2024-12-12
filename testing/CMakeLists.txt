# Google Test einbinden

# Testdateien sammeln
set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/bounding_boxTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guiTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/kitti_datasetTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mode1Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mode2Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mode3Test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/playerTest.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests gtest gmock gtest_main)


enable_testing()

