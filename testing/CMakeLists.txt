# Google Test einbinden
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

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


add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests gtest gmock gtest_main)

# Include-Verzeichnisse hinzufügen
target_include_directories(unit_tests PRIVATE
    ${gtest_SOURCE_DIR}/googletest/include
    ${gtest_SOURCE_DIR}/googlemock/include
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(unit_tests)
