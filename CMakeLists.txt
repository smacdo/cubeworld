###########################################################################
# CubeWorld                                                               #
# (c) 2010 Scott MacDonald                                                #
#                                                                         #
# Build system script                                                     #
###########################################################################
cmake_minimum_required(VERSION 2.6)
project(CubeWorldGame)

#==========================================================================
# Build settings and configurations
#==========================================================================
set(APP_BIN_NAME "cubeworld_client")

#==========================================================================
# Build setup and paths
#==========================================================================
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extra/cmake")
include(${CMAKE_SOURCE_DIR}/extra/cmake/shared.cmake)

set(GTEST_ROOT     "${PROJECT_SOURCE_DIR}/extra/googletest")
set(LIBS_ROOT      "${PROJECT_SOURCE_DIR}/libs")
set(XLIBS_ROOT     "${PROJECT_SOURCE_DIR}/extra")
set(GLUT_ROOT_PATH "$ENV{API_DIR}/freeglut")

#==========================================================================
# Build options
#==========================================================================
option(BUILD_RELEASE "Build application with all optimizations enabled" OFF)
option(BUILD_DEBUG   "Build application with debugging symbols"          ON)
option(STRICT_WARNS  "Enable strict warnings"                            ON)
option(ENABLE_TESTS  "Enable building of unit tests"                     ON)

#==========================================================================
# Build configuration
#==========================================================================
if(MSVC)
	# Enable security checks
	set(cxx_flags "${cxx_flags} /Gs")
	
	# Set strictest warning settings and treat them as errors
	if(STRICT_WARNS)
		set(cxx_flags "${cxx_flags} /W4")
	endif()
	
	# Disable several level 4 warnings about ansi compliance
	#  (-wNNN)
	#   - Not using Microsoft's 'secure' file functions
	#   - Dead functions generated from glut
	#   - Non-existant PDB files (we should probably fix this)
	set(cxx_flags "${cxx_flags} /wd4996 /wd4505 /wd4099")
	
	# Misc options
	#   J: Make visual studio treat chars as unsigned rather than signed
	#  Zi: Generate PDB for debugging
	#  Wx: Warnings are errors (temporarily removed)
	set(cxx_flags "${cxx_flags} /arch:SSE2 /nologo /J /Zi")
	
	# Defines specific for windows platform
    set(cxx_flags "${cxx_flags} /DWIN32_LEAN_AND_MEAN")
	
elseif(CMAKE_COMPILER_IS_GNUCXX)
    # Enable stricter warnings
	if(STRICT_WARNS)
		set(cxx_flags "${cxx_flags} -Wall -Wextra")
	endif()

    # Misc. settings
    set(cxx_flags "${cxx_flags} -msse2 -Werror")
endif()

#
# Linking configuration - are we creating a release, release w/ deb info,
# or a debug build?
#
if(BUILD_RELEASE)
    message(STATUS "Building in release mode")
	
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(cxx_flags "${cxx_flags} -O2 -fomit-frame-pointer")
	endif()
elseif(BUILD_RELEASE AND BUILD_DEBUG)
    message(STATUS "Building in release mode with debug symbols enabled")
	
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(cxx_flags "${cxx_flags} -O2 -ggdb")
	endif()
elseif(BUILD_DEBUG)
    message(STATUS "Building in debug mode")
	
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(cxx_flags "${cxx_flags} -ggdb")
	endif()
else()
    message(FATAL_ERROR "Unknown build mode specified")
endif()

#==========================================================================
# Pull in all the subdirectory build scripts so we can build everything
#==========================================================================
add_subdirectory(${XLIBS_ROOT})
add_subdirectory(${LIBS_ROOT})
add_subdirectory(src)

IF(ENABLE_TESTS)
    # Tests disabled under refactor finished
    #    add_subdirectory(${GTEST_PATH})
    #    add_subdirectory(tests)
ENDIF()
