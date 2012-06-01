#########################################################################
# Common libs
# -----------
#
# This subdirectory provides re-usable unit tested classes and functions
# to accomplish useful functionality including core common code, string
# manipulation, math calculations and geometry processing
#
# You do not need to use everything in here, just remove the libraries
# that you are not interested in :)
########################################################################
project(commonlibs)
set(COMMON_LIBS_VERSION 3)

cmake_minimum_required(VERSION 2.8)

#=========================================================================#
# libcommon components                                                    #
#=========================================================================#
set( libcommon_incs  "" )
set( libcommon_srcs  "" )
set( libcommon_tests "" )

add_subdirectory(common)
add_subdirectory(math)
add_subdirectory(app)
add_subdirectory(string)
#add_subdirectory(game2d)
add_subdirectory(game3d)

#=========================================================================#
# External libraries                                                      #
#=========================================================================#
set(Boost_USE_STATIC_LIBS true)
find_package(Boost REQUIRED)

#=========================================================================#
# Compiler settings and configuration                                     #
#=========================================================================#
set( CXX_FLAGS "" )

if(MSVC)
	# Disable several strict visual studio warnings
	#	- nameless unions/structs is non-standard
	#	- conditional expression is constant ( assert( x && "..." ) )
	#	- unknown pragma
	#   - remove warnings about not using microsoft's 'safe' functions
	set(CXX_FLAGS "${CXX_FLAGS} /wd4201 /wd4127 /wd4068 /wd4996")

	if(libcommon_assert)
		set(CXX_FLAGS "${CXX_FLAGS} /DNDEBUG=1=1 /D_DEBUG=1")
	endif()

	if(libcommon_debug)
		set(CXX_FLAGS "${CXX_FLAGS} /GS /Zi")
	endif()

	if(libcommon_performance)
		set(CXX_FLAGS "${CXX_FLAGS} /Ot /arch:SSE2")
	endif()
else()
	if(libcommon_cpp0x)
		set(CXX_FLAGS "${CXX_FLAGS} -std=c++0x")
	endif()

	if(libcommon_assert)
		set(CXX_FLAGS "${CXX_FLAGS} -DNDEBUG=1 -D_DEBUG=1")
	endif()

	if(libcommon_debug)
		set(CXX_FLAGS "${CXX_FLAGS} -ggdb")
	endif()

	if(libcommon_performance)
		# clang does not support -mfpmath=sse
		set(CXX_FLAGS "${CXX_FLAGS} -mtune=native -msse2 -msse3")
	endif()
endif()

#=========================================================================#
# Warning configuration                                                   #
#=========================================================================#
if(MSVC)
	if(libcommon_warnings)
		set(CXX_FLAGS "${CXX_FLAGS} /W3 /WX" )
	endif()
elseif()
	if(libcommon_warnings)
		set(CXX_FLAGS "${CXX_FLAGS} -Wall -Werror" )
	endif()

	if(libcommon_more_warnings)
		set(CXX_FLAGS "${CXX_FLAGS} -Wextra -Winit-self -Wswitch-enum" )
		set(CXX_FLAGS "${CXX_FLAGS} -Wuninitialized -Wfloat-equal -Wsign-conversion" )
		set(CXX_FLAGS "${CXX_FLAGS} -Wpointer-arith -Wconversion" )
		set(CXX_FLAGS "${CXX_FLAGS} -Wctor-dtor-privacy -Wnon-virtual-dtor" )
		set(CXX_FLAGS "${CXX_FLAGS} -Woverloaded-virtual" )
	endif()

	if(libcommon_extra_warnings)
		set(CXX_FLAGS "${CXX_FLAGS} -Wlogical-op -Wdouble-promotion")
		set(CXX_FLAGS "${CXX_FLAGS} -Wnarrowing" )
		set(CXX_FLAGS "${CXX_FLAGS} -Wzero-as-null-pointer-constant" )
	endif()
endif()

#=========================================================================#
# Apply all compile flags to the source code and header files             #
#=========================================================================#
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

set_source_files_properties(
    ${libcommon_incs}
    ${libcommon_srcs}
    PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}"
)

#=========================================================================#
# Generate a static library to hold all of the common code for use        #
# in our other projects                                                   #
#=========================================================================#
add_library(common STATIC ${libcommon_srcs} ${libcommon_incs} )

#=========================================================================#
# Create a program that executes all of libcommon's unit tests            #
#=========================================================================#
if(build_libcommon_tests)
    # Make sure that test runner can #include google test
    include_directories( ${CMAKE_SOURCE_DIR}/thirdparty/googletest/include )

    # Need C++0x support and basic warnings enabled for the unit tests
    set_source_files_properties(
        testrunner.cpp ${libcommon_tests}
		PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
#        COMPILE_FLAGS "-DNDEBUG=1 -D_DEBUG=1 -Wall -Werror -ggdb -std=c++0x")

    # Generate the executable now
    add_executable( test_commonlibs testrunner.cpp ${libcommon_tests} )

    # Need libraries obviously
    target_link_libraries( test_commonlibs common googletest )

    # Special targets that will run the unit test
	if ( NOT MSVC )
	    add_custom_target(
			libcommon-tests ${CMAKE_CURRENT_BINARY_DIR}/test_commonlibs
			DEPENDS test_commonlibs )
	
		# Run with GDB
		add_custom_target(
			test-gdb
			gdb `pwd`/test_commonlibs -d ${PROJECT_SOURCE_DIR} -cd ${PROJECT_SOURCE_DIR}
			DEPENDS test_commonlibs
			COMMENT "Running unit tests with GDB" )

		# Run with valgrind
		add_custom_target(
			test-valgrind
			COMMAND ${CMAKE_SOURCE_DIR}/scripts/run_memgrind.sh
					${CMAKE_CURRENT_BINARY_DIR}/test_commonlibs
			DEPENDS test_commonlibs
			COMMENT "Running unit tests with valgrind")
	endif()
endif()
