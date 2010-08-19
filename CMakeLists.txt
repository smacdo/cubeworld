cmake_minimum_required(VERSION 2.6)
project(ScottsRoguelike)

#######################################################################
### Build system properties
#######################################################################
set(BIN_NAME rogue)

#######################################################################
### CMake Required Modules
#######################################################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extra/cmake")

find_package(Curses REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
find_package(OpenGL REQUIRED)

#######################################################################
### Build system options and flags
#######################################################################
OPTION(OPT_DEBUG     "Enable application debugging" ON)
OPTION(OPT_TESTING   "Enable unit testing" ON)
OPTION(OPT_ENGINELIB "Generate a engine library" OFF)

IF(OPT_DEBUG)
    #    add_subdirectory(tests)
    SET(CMAKE_BUILD_TYPE Debug)
ELSE(OPT_DEBUG)
    SET(CMAKE_BUILD_TYPE ReleaseWithDebInfo)
ENDIF(OPT_DEBUG)

#######################################################################
### Visual Studio specific options
#######################################################################
IF(WIN32)
    #    set_target_properties(glsandbox PROPERTIES 
    #                      LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
ENDIF(WIN32)

###
### Enable C++0x
###
set(CMAKE_CXX_FLAGS "-std=c++0x")

#######################################################################
### Build all required libraries, game code tests and whatnot
#######################################################################
include_directories(include)
add_subdirectory(extra/googletest)
add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(tests)

#######################################################################
### Post-build steps
#######################################################################
