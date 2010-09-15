#########################################################################
### Project source build script                                       ###
###  - This portion of the build will compile all testable code into  ###
###    a static library, and then link the entire project binary      ###
###    together along with any required libraries and settings        ###
#########################################################################
# List of application's source code files that will be placed under test
SET(applib_srcs gameworld.cpp
                typesio.cpp
                camera.cpp
                cubeworld.cpp
                gameapp.cpp)

# The rest of the application's code (anything not under test)
SET(appcore_srcs rogue.cpp renderers/opengl.cpp)

#========================================================================
# Internal engine libraries
#========================================================================
set(ENGINE_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/libs/appcore/include"
                        "${CMAKE_SOURCE_DIR}/libs/math/include")
set(ENGINE_LIBS appcore tga math)

#========================================================================
# External required libraries
#========================================================================
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)
find_package(OpenGL REQUIRED)

# Pull in required third party libraries (OpenGL, etc)
set(APP_LIBS ${EXTRA_LIBS} 
             ${GLUT_LIBRARIES}
             ${OpenGL_LIBRARIES}
             ${GLU_LIBRARY})
set(APP_LIB_INCLUDE_DIRS )

#========================================================================
# Application compiling and linking
#========================================================================
# Set up include directories
include_directories( ${CMAKE_SOURCE_DIR}/include
                     ${CMAKE_APP_LIB_INCLUDE_DIRS}
                     ${ENGINE_INCLUDE_DIRS} )

# Create the actual library (of code under test), and executable that
# contains all code
add_library(applib STATIC ${applib_srcs})
add_executable(${APP_BIN_NAME} ${appcore_srcs})

# Link any needed libraries
target_link_libraries(${APP_BIN_NAME} applib ${ENGINE_LIBS} ${APP_LIBS})

# Apply flags as needed
set_target_properties(applib PROPERTIES
                      COMPILE_FLAGS "${cxx_flags}")
set_target_properties(${APP_BIN_NAME} PROPERTIES
                      COMPILE_FLAGS "${cxx_flags}")

#==========================================================================
# Run the target
#==========================================================================
add_custom_target(run ${APP_BIN_NAME} DEPENDS ${APP_BIN_NAME}
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                  COMMENT "Runs the application")

add_custom_target(debug 
                  gdb `pwd`/${APP_BIN_NAME} -d ${PROJECT_SOURCE_DIR}/src -cd
                  ${PROJECT_SOURCE_DIR}
                  DEPENDS ${APP_BIN_NAME}
                  COMMENT "Run application with GDB support")
