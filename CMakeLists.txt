###########################################################################
# Project Forge                                                           #
# (c) 2010 Scott MacDonald                                                #
#                                                                         #
# Build system script                                                     #
###########################################################################
cmake_minimum_required(VERSION 2.6)
project(ScottsRoguelike)

#==========================================================================
# Build settings and configurations
#==========================================================================
set(APP_BIN_NAME "forgeclient")

#==========================================================================
# Build setup and paths
#==========================================================================
set(GTEST_PATH "${PROJECT_SOURCE_DIR}/thirdparty/googletest")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/cmake")

set(GLUT_ROOT_PATH "$ENV{API_DIR}/freeglut")

#==========================================================================
# Build options
#==========================================================================
option(BUILD_RELEASE "Build application with all optimizations enabled" OFF)
option(BUILD_DEBUG   "Build application with debugging symbols"          ON)
option(ENABLE_TESTS  "Enable building of unit tests"                     ON)

#==========================================================================
# Build configuration
#==========================================================================
# 
# Set standard C++ compiler flags
#
if(MSVC)
    set(cxx_flags "${cxx_flags} -GS -W4 -WX")
    set(cxx_flags "${cxx_flags} -wd4127 -wd4251 -wd4275 -nologo -J -Zi")
    set(cxx_flags "${cxx_flags} -DSTRICT -DWIN32_LEAN_AND_MEAN")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    # Enable stricter warnings
    # set(cxx_flags "${cxx_flags} -Wall -Wextra -Wshadow")

    # Enable SSE1 and SSE2 extensions
    set(cxx_flags "${cxx_flags} -msse2")
endif()

#
# Linking configuration - are we creating a release, release w/ deb info,
# or a debug build?
#
if(BUILD_RELEASE)
    message(STATUS "Building in release mode")
    set(cxx_flags "${cxx_flags} -O2 -fomit-frame-pointer")
elseif(BUILD_RELEASE AND BUILD_DEBUG)
    message(STATUS "Building in release mode with debug symbols enabled")
    set(cxx_flags "${cxx_flags} -O2 -ggdb")
elseif(BUILD_DEBUG)
    message(STATUS "Building in debug mode")
    set(cxx_flags "${cxx_flags} -ggdb")
else()
    message(FATAL_ERROR "Unknown build mode specified")
endif()

#==========================================================================
# Pull in all the subdirectory build scripts so we can build everything
#==========================================================================
add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(libs)

IF(ENABLE_TESTS)
    add_subdirectory(${GTEST_PATH})
    #    add_subdirectory(tests)
ENDIF()
