#########################################################################
### Project source build script                                       ###
###  - This portion of the build will compile all testable code into  ###
###    a static library, and then link the entire project binary      ###
###    together along with any required libraries and settings        ###
#########################################################################
# Core source code files that comprise cube world's game engine. This is
# all non-client presentation code
SET(engine_srcs
        engine/camera.cpp
        engine/constants.cpp
        engine/cubedata.cpp
        engine/intersection.cpp
        engine/material.cpp
        engine/point.cpp
        engine/worldchunk.cpp
        engine/world.cpp
        graphics/worldview.cpp
        world/worldgenerator.cpp
)
		
# Client code that is not under test
SET(game_srcs
        graphics/worldchunkbuilder.cpp
        graphics/opengl/renderer.cpp
        rogue.cpp
)

#========================================================================
# External required libraries
#========================================================================
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLU REQUIRED)

# Pull in required third party libraries (OpenGL, etc)
set(APP_LIBS ${EXTRA_LIBS} 
             ${GLUT_LIBRARIES}
             ${OpenGL_LIBRARIES}
             ${GLEW_LIBRARY}
             ${GLU_LIBRARY}
             common
             lodepng)
	
#========================================================================
# Application compiling and linking
#========================================================================
# Set up include directories
include_directories( ${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}/libcommon )

if(MSVC)
    # Temporary hack to force static libs. Will want to switch to DLLs
    add_definitions("-DFREEGLUT_STATIC -DGLEW_STATIC")
endif()
					 
# Create a static library for the cubeworld game engine code. This will 
# seperate the client from the actual game logic.
add_library(cubeworld_engine STATIC ${engine_srcs})
set_target_properties(cubeworld_engine PROPERTIES COMPILE_FLAGS "${cxx_flags}")

# Create the executable that will run the game client
#add_executable(${APP_BIN_NAME} ${game_srcs})
#set_target_properties(${APP_BIN_NAME} PROPERTIES COMPILE_FLAGS "${cxx_flags}")
#target_link_libraries(${APP_BIN_NAME} cubeworld_engine ${ENGINE_LIBS} ${APP_LIBS})

#==========================================================================
# Copy and configure needed files
#==========================================================================
configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#==========================================================================
# Run the target
#==========================================================================
if(NOT MSVC)
    add_custom_target(run ${APP_BIN_NAME} DEPENDS ${APP_BIN_NAME}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                      COMMENT "Runs the cube world client")

    add_custom_target(debug 
                     gdb `pwd`/${APP_BIN_NAME} -d ${PROJECT_SOURCE_DIR}/src -cd
                     ${PROJECT_SOURCE_DIR}
                     DEPENDS ${APP_BIN_NAME}
                     COMMENT "Run cubeworld client with GDB support")

    add_custom_target(doxygen
                      doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                      COMMENT "Generates doxygen documentation")
endif()
