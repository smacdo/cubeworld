###########################################################################
# CubeWorld                                                               #
# (c) 2010-2012 Scott MacDonald                                           #
#                                                                         #
# Build system script                                                     #
###########################################################################
cmake_minimum_required(VERSION 2.8)
project(CubeWorldGame)

#=========================================================================#
# Load common cmake modules to incorporate functionality not found in     #
# standard CMake distribution                                             #
#=========================================================================#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include( config )
include( GetGitRevisionDescription )
include( GetCompilerInfoString )
include( EnableExtraCompilerWarnings )
include( MSVCMultipleProcessCompile )
include( SandboxBuildRules )

set(GLUT_ROOT_PATH "$ENV{API_DIR}/freeglut")
add_definitions("-DUSE_BOOST")

#==========================================================================
# Build configuration
#==========================================================================
if(MSVC)
	# Libcommon flags and other global flags
	set(cxx_flags "${cxx_flags} /DNDEBUG=1=1 /D_DEBUG=1 /DUNICODE /D_UNICODE")

	# Enable security checks
	set(cxx_flags "${cxx_flags} /Gs")

	# Disable several level 4 warnings about ansi compliance
	#  (-wNNN)
	#   - Not using Microsoft's 'secure' file functions
	#   - Dead functions generated from glut
	#   - Non-existant PDB files (we should probably fix this)
	#	- Warning about nameless struct/union
	#	- conditional expression is constant ( assert( x && "..." ) )
	#	- unknown pragma
	set(cxx_flags "${cxx_flags} /wd4996 /wd4505 /wd4099 /wd4201 /wd4127 /wd4068")
	
	# Misc options
	#   J: Make visual studio treat chars as unsigned rather than signed
	#  Zi: Generate PDB for debugging
	set(cxx_flags "${cxx_flags} /arch:SSE2 /nologo /J /Zi")
	
	# Defines specific for windows platform
    set(cxx_flags "${cxx_flags} /DWIN32_LEAN_AND_MEAN")
	
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(cxx_flags "${cxx_flags} -DNDEBUG=1 -D_DEBUG=1 -ggdb ")
    set(cxx_flags "${cxx_flags} -std=c++0x -Wall -Wextra -Werror")

    # Misc. settings
    set(cxx_flags "${cxx_flags} -msse2 -Werror")
endif()

set( THIRD_PARTY_ROOT "${CMAKE_SOURCE_DIR}/thirdparty" )
add_subdirectory(thirdparty)
add_subdirectory(libcommon)
add_subdirectory(src)
add_subdirectory(tests)
