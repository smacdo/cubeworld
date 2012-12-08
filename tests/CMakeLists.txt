###########################################################################
### Project tests build script                                          ###
###  - This portion of the build will compile all of the project's unit ###
###    tests, link them into the google test runner and produce a       ###
###    simple command line binary that runs the tests.                  ###
###########################################################################
set(test_srcs
    test_alwaystrue.cpp
    test_flatworld.cpp
    test_worldchunk.cpp
    test_world.cpp
)

#==========================================================================
# Compile and link tests
#==========================================================================
include_directories( ${PROJECT_SOURCE_DIR}/src
                     ${PROJECT_SOURCE_DIR}/libcommon
                     ${PROJECT_SOURCE_DIR}/thirdparty/googletest/include)

add_executable(
    cubeworld-engine-test
    ${test_srcs}   
    ${PROJECT_SOURCE_DIR}/src/graphics/null/nullrenderer.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/null/nullwindow.cpp
    ${PROJECT_SOURCE_DIR}/thirdparty/googletest/testrunner.cpp )

set_target_properties(
    cubeworld-engine-test
    PROPERTIES COMPILE_FLAGS "${cxx_flags}")

target_link_libraries( cubeworld-engine-test
                       cubeworld_engine googletest common )

if ( NOT MSVC )
	add_custom_target(tests ALL cubeworld-engine-test
					  DEPENDS cubeworld-engine-test
					  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
					  COMMENT Runs application unit tests)
endif()
