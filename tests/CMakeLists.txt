###########################################################################
### Project tests build script                                          ###
###  - This portion of the build will compile all of the project's unit ###
###    tests, link them into the google test runner and produce a       ###
###    simple command line binary that runs the tests.                  ###
###########################################################################
set(test_srcs test_alwaystrue.cpp
              test_octreeworld.cpp
              test_point.cpp)

#==========================================================================
# Extra code libraries config
#==========================================================================
set(test_include_dirs ${CMAKE_SOURCE_DIR}/libs/math/include )
set(test_libs math)

#==========================================================================
# Compile and link tests
#==========================================================================
# Required #include paths
include_directories( ${PROJECT_SOURCE_DIR}/include
                     ${test_include_dirs}
                     ${GTEST_PATH}/include )

# Google test requires a pthreads library
find_package(Threads REQUIRED)

# Link the executable
add_executable(test-${APP_BIN_NAME}
               ${test_srcs}
               ${GTEST_PATH}/googletestrunner.cpp )

target_link_libraries(test-${APP_BIN_NAME} applib ${test_libs} gtest)
#set_target_properties(test-${APP_BIN_NAME}
#                      PROPERTIES
#                      LINK_FLAGS ${CMAKE_THREAD_LIBS_INIT})

add_custom_target(tests ALL test-${APP_BIN_NAME}
                  DEPENDS test-${APP_BIN_NAME}
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  COMMENT Runs application unit tests)
