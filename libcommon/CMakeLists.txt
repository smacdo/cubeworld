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
set(COMMON_LIBS_VERSION 5)

cmake_minimum_required(VERSION 2.8)

#=========================================================================#
# Required external libraries and modules                                 #
#=========================================================================#
include(CheckCXXCompilerFlag)

set(Boost_USE_STATIC_LIBS true)
find_package(Boost REQUIRED)


#=========================================================================#
# libcommon components                                                    #
#=========================================================================#
set( libcommon_incs  "" )
set( libcommon_srcs  "" )
set( libcommon_tests "" )

add_subdirectory(common)
add_subdirectory(math)
add_subdirectory(app)
add_subdirectory(platform)
#add_subdirectory(entity)
add_subdirectory(game2d)
add_subdirectory(game3d)
add_subdirectory(string)

#=========================================================================#
# Options for building libcommon                                          #
#=========================================================================#
option(build_libcommon_tests    "Build libcommon unit tests" on)
option(libcommon_cpp0x          "Build libcommon with C++0x support" on)
option(libcommon_assert         "Build libcommon with custom asserts" on)
option(libcommon_debug          "Build libcommon with debugging support" on)
option(libcommon_warnings       "Build libcommon with warnings" on)
option(libcommon_performance    "Build libcommon with performance flags" on)

option(MATH_TYPEDEFS "Define common math types" ON)
option(MATH_FUZZY_EQUALS "Use fuzzy equal for floating point" ON)
option(MATH_DOUBLE "Use double precision floating point" OFF)
option(MATH_DEBUG "Enable math debugging (slow)" ON)

#=========================================================================#
# Compiler settings and configuration                                     #
#=========================================================================#
set( CXX_FLAGS "" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${THIRD_PARTY_ROOT} )

if(libcommon_cpp0x)
	if(NOT MSVC)
		set(CXX_FLAGS "${CXX_FLAGS} -std=c++0x")
	endif()
endif()

if(libcommon_assert)
	if(MSVC)
		set(CXX_FLAGS "${CXX_FLAGS} /DENABLE_ASSERT_HANDLER")
	else()
		set(CXX_FLAGS "${CXX_FLAGS} -DENABLE_ASSERT_HANDLER")
	endif()
endif()

if(libcommon_debug)
	if(MSVC)
		set(CXX_FLAGS "${CXX_FLAGS} /GS /Zi")
	else()
		set(CXX_FLAGS "${CXX_FLAGS} -ggdb")
	endif()
endif()

if(libcommon_performance)
    # GCC / CLANG support
    if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX )
        # Enable support for SSE3. All CPUs since 2004 (Prescott Pentium 4)
        # have full support for SSE3.
        check_cxx_compiler_flag(-msse3 HAS_SSE3)
        if( HAS_SSE3 )
            set(CXX_FLAGS "${CXX_FLAGS} -msse")
        endif()

        check_cxx_compiler_flag(-mfpmath HAS_FPMATH)
        if ( HAS_FPMATH )
            set(CXX_FLAGS "${CXX_FLAGS} -mfpmath=sse")
        endif()
    endif()

    # MSVC support
    if( MSVC )
        # Might need to alter this... depends on how well fp:fast functions
        # under load
        set( CXX_FLAGS "${CXX_FLAGS} /fp:fast" )

        # Enable instrinsics even in debug
        set( CXX_FLAGS "${CXX_FLAGS} /Oi /Ot /arch:SSE2" )
    endif()
endif()

#
# Visual Studio specific settings
#
if ( MSVC )
	# Disable several strict visual studio warnings
	#	- nameless unions/structs is non-standard
	#	- conditional expression is constant ( assert( x && "..." ) )
	#	- unknown pragma
	#   - remove warnings about not using microsoft's 'safe' functions
	set(CXX_FLAGS "${CXX_FLAGS} /wd4201 /wd4127 /wd4068 /wd4996")

    if ( CMAKE_CL_64 )
        # VS errors out in 64 bit debug builds for some reason
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj")
    endif()
endif()

#=========================================================================#
# Build sanity tests                                                      #
#=========================================================================#
if( NOT DEFINED THIRD_PARTY_ROOT )
    message( SEND_ERROR "THIRD_PARTY_ROOT was not defined" )
endif()

#=========================================================================#
# Set up the basic build environment                                      #
#=========================================================================#
# Are we building 32 bit or 64 bit?
include( CheckTypeSize )
CHECK_TYPE_SIZE( "void*" LIBCOMMON_PTR_SIZE BUILTIN_TYPES_ONLY )

if ( LIBCOMMON_PTR_SIZE EQUAL 8 )
    message( "64bit build selected" )
    set( LIBCOMMON_X64 TRUE )
else()
    message( "32bit build selected" )
    set( LIBCOMMON_X64 FALSE)
endif()

# Create debug libraries with _d
if ( NOT APPLE )
    set( CMAKE_DEBUG_POSTFIX "_d" )
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
    PROPERTIES COMPILE_FLAGS "${CXX_FLAGS} ${LIBCOMMON_FLAGS}"
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
    include_directories( ${THIRD_PARTY_ROOT}/googletest/include )

    # Need threads support
    find_package(Threads)

    # Need to have C++0x support turned on
	set(TESTING_CPP_FLAGS "")
	
	if(MSVC)
		set(TESTING_CPP_FLAGS "/DENABLE_ASSERT_HANDLER")
	else()
		set(TESTING_CPP_FLAGS "-ggdb -std=c++0x -DENABLE_ASSERT_HANDLER")
	endif()
	
    set_source_files_properties(
        testing/runner.cpp
        testing/testing.cpp
        ${libcommon_tests} PROPERTIES
        COMPILE_FLAGS "${TESTING_CPP_FLAGS}")

    # Generate the executable now
    add_executable( test_commonlibs
                    testing/runner.cpp
                    testing/testing.cpp
                    ${libcommon_tests} )

    # ... with warnings
    enable_warnings( test_commonlibs )

    # Need libraries obviously
    target_link_libraries( test_commonlibs
        common
        googletest
        ${CMAKE_THREAD_LIBS_INIT} )

    # Add a custom target to run the unit tests
	if ( NOT MSVC )
		add_custom_target(
			test ${CMAKE_CURRENT_BINARY_DIR}/test_commonlibs
			DEPENDS test_commonlibs )

		# Add custom target that launches unit tests with gdb
		add_custom_target(
			test-gdb
			gdb `pwd`/test_commonlibs -d ${PROJECT_SOURCE_DIR} -cd ${PROJECT_SOURCE_DIR}
			DEPENDS test_commonlibs
			COMMENT "Running unit tests with GDB" )

		add_custom_target(
			test-valgrind
			COMMAND ${CMAKE_SOURCE_DIR}/scripts/run_memgrind.sh
					${CMAKE_CURRENT_BINARY_DIR}
					test_commonlibs
					test_commonlibs
			DEPENDS test_commonlibs
			COMMENT "Running unit tests with valgrind")
	endif()
endif()
