#########################################################################
### Project source build script                                       ###
###  - This portion of the build will compile all testable code into  ###
###    a static library, and then link the entire project binary      ###
###    together along with any required libraries and settings        ###
#########################################################################
#========================================================================
# Game engine and gameplay code
#========================================================================
SET(engine_srcs
        engine/camera.cpp
        engine/constants.cpp
        engine/cubedata.cpp
        engine/intersection.cpp
        engine/material.cpp
        engine/point.cpp
        engine/worldchunk.cpp
        engine/world.cpp
        graphics/iwindow.cpp
        graphics/worldview.cpp
        world/worldgenerator.cpp
)

set(engine/includes
	engine/camera.h
	engine/constants.h
	engine/cubedata.h
	engine/cubeintersection.h
	engine/gametime.h
	engine/material.h
	engine/point.h
	engine/world.h
	engine/worldchunk.h
	engine/worldcube.h
    graphics/irenderer.h
    graphics/iwindow.h
    graphics/worldview.h
)

# Application code that is not under unit test... this is generally the
# platform specific graphics code and whatnot
set(game_srcs
	cubeworld.cpp
	gameclient.cpp
)

set(game_incs
	cubeworld.h
	gameclient.h
)

set(platform_srcs "")
set(platform_incs "")

#========================================================================
# Platform specific game code
#========================================================================
if(MSVC)
	set(winplatform_srcs
		winmain.cpp
	)

	set(renderer_srcs
		graphics/directx/dxaboutbox.cpp
		graphics/directx/dxrenderer.cpp
		graphics/directx/dxwindow.cpp
	)
	
	set(renderer_incs
		graphics/directx/dxaboutbox.h
		graphics/directx/dxrenderer.h
		graphics/directx/dxwindow.h
	)
	
	set(platform_srcs ${winplatform_srcs} ${renderer_srcs})
	set(platform_incs ${renderer_incs})
else()
	SET(platform_srcs
        linuxmain.cpp
        graphics/null/nullrenderer.cpp
        graphics/null/nullwindow.cpp
	)
endif()

#========================================================================
# External libraries
#========================================================================
set(Boost_USE_STATIC_LIBS true)
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

if(MSVC)
	# Locate platform specific libraries
	find_package(DirectX REQUIRED)
	
	# DirectX 11 is REQUIRED
	if ( NOT DirectX_D3D11_FOUND )
		message( "DirectX SDK located" )
		message( SEND_ERROR "DirectX 11 SDK is required" )
	endif()
	
	# Build the library and include directories list
	set( APP_INCS ${DirectX_D3D11_INCLUDE_DIR} )
	set( APP_LIBS ${DirectX_D3D11_LIBRARIES} )
else()
	# Locate platform specific libraries
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(GLU REQUIRED)
	
	# Build the library and include directories list
	set( APP_LIBS ${GLUT_LIBRARIES} ${OpenGL_LIBRARIES} ${GLEW_LIBRARY} ${GLU_LIBRARY} )
endif()
	
#========================================================================
# Shared engine library
#  (This is all the non-platform specific code that we can unit test)
#========================================================================
# Set up include directories
include_directories(
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/libcommon
	${Boost_INCLUDE_DIRS}
)
					 
# Create a static library for the cubeworld game engine code. This will 
# seperate the client from the actual game logic.
add_library( cubeworld_engine STATIC ${engine_srcs} ${engine_incs})
set_target_properties(cubeworld_engine PROPERTIES COMPILE_FLAGS "${cxx_flags}")
target_link_libraries(cubeworld_engine common ${Boost_LIBRARIES})

#========================================================================
# Game client executable
#  (This is actual runnable game)
#========================================================================
add_executable(cubeworld_client
	${game_srcs} ${game_incs}
	${graphics_srcs} ${graphics_incs}
	${platform_srcs} ${platform_incs}
)
set_target_properties(cubeworld_client PROPERTIES COMPILE_FLAGS "${cxx_flags}")
target_link_libraries(cubeworld_client
                        common cubeworld_engine googletest
                        ${APP_LIBS}
                        ${Boost_LIBRARIES})

#==========================================================================
# Copy and configure needed files
#==========================================================================
configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#==========================================================================
# Run the target
#==========================================================================
if(NOT MSVC)
    add_custom_target(run cubeworld_client DEPENDS cubeworld_client
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                      COMMENT "Runs the cube world client")

    add_custom_target(debug 
                     gdb `pwd`/cubeworld_client -d ${PROJECT_SOURCE_DIR}/src -cd
                     ${PROJECT_SOURCE_DIR}
                     DEPENDS cubeworld_client
                     COMMENT "Run cubeworld client with GDB support")

    add_custom_target(doxygen
                      doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                      COMMENT "Generates doxygen documentation")
endif()
