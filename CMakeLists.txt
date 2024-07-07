cmake_minimum_required(VERSION 3.14)
project(gol)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define c standard to be used (20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Require gtest dependency
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(gol src/main/main.cpp)

# Setup testing
enable_testing()
add_executable(pattern_test src/test/pattern_test.cpp)
target_link_libraries(pattern_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(pattern_test)
