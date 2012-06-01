###########################################################################
# CubeWorld                                                               #
# (c) 2010 Scott MacDonald                                                #
#                                                                         #
# Build system script                                                     #
###########################################################################
cmake_minimum_required(VERSION 2.8)
project(CubeWorldGame)

#==========================================================================
# Build setup and paths
#==========================================================================
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/thirdparty/cmake")
set(GLUT_ROOT_PATH "$ENV{API_DIR}/freeglut")

#==========================================================================
# Options
#==========================================================================
option(build_libcommon_tests    "Build libcommon unit tests" on)
option(libcommon_cpp0x          "Build libcommon with C++0x support" on)
option(libcommon_assert         "Build libcommon with custom asserts" on)
option(libcommon_debug          "Build libcommon with debugging support" on)
option(libcommon_warnings       "Build libcommon with warnings" on)
option(libcommon_more_warnings  "Build libcommon with lots of warnings" off)
option(libcommon_extra_warnings "Build libcommon with all the warnings" off)
option(libcommon_performance    "Build libcommon with performance flags" on)

#==========================================================================
# Build options
#==========================================================================
option(STRICT_WARNS  "Enable strict warnings"                        ON)

#==========================================================================
# Build configuration
#==========================================================================
if(MSVC)
	# Libcommon flags and other global flags
	set(cxx_flags "${cxx_flags} /DNDEBUG=1=1 /D_DEBUG=1")

	# Enable security checks
	set(cxx_flags "${cxx_flags} /Gs")
	
	# Set strictest warning settings and treat them as errors
	if(STRICT_WARNS)
		set(cxx_flags "${cxx_flags} /W4")
	else()
		set(cxx_flags "${cxx_flags} /W3 /Wx")
	endif()
	
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
    set(cxx_flags "${cxx_flags} -DNDEBUG=1 -D_DEBUG=1")
    set(cxx_flags "${cxx_flags} -std=c++0x -Wall -Wextra -Werror")

    # Misc. settings
    set(cxx_flags "${cxx_flags} -msse2 -Werror")
endif()

add_subdirectory(thirdparty)
add_subdirectory(libcommon)
add_subdirectory(src)
add_subdirectory(tests)
