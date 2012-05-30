project(GoogleTestLib)
cmake_minimum_required(VERSION 2.6)

# Disable threads (for the moment)
add_definitions(-DGTEST_HAS_PTHREAD=0)

# Set global property that tells everyone where Google Test is, and
# how it is configured
set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "N/A")
set(GTEST_RUNNER_PATH "${GTEST_PATH}/testrunner.cpp"
    CACHE INTERNAL "N/A")

# Build Google test as a static library
include_directories(${GTEST_PATH}/include)
set_source_files_properties(
    gtest-all.cpp PROPERTIES COMPILE_FLAGS "-std=c++0x")
add_library(googletest STATIC gtest-all.cpp)
