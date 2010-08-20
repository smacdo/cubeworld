#######################################################################
### List of application test files
#######################################################################
set(test_srcs test_alwaystrue.cpp
              test_octreeworld.cpp
              test_point.cpp)

#######################################################################
### Google Test setup
#######################################################################
include_directories(${CMAKE_SOURCE_DIR}/extra/googletest/include
                    ${CMAKE_SOURCE_DIR}/libs/math/include)
SET(testrunner_src ${CMAKE_SOURCE_DIR}/extra/googletest/testrunner.cpp)

#######################################################################
### Create the test runner
#######################################################################
find_package(Threads REQUIRED)

add_executable( testrunner-${BIN_NAME} ${test_srcs} ${testrunner_src} )
target_link_libraries( testrunner-${BIN_NAME} googletest rogue_engine math)

set_target_properties(testrunner-${BIN_NAME}
    PROPERTIES
    LINK_FLAGS ${CMAKE_THREAD_LIBS_INIT})
