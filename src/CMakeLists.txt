#######################################################################
### Project specific source code
#######################################################################
# Game sources
SET(game_srcs gameworld.cpp typesio.cpp camera.cpp gameapp.cpp)

# Application level logic (main, gui, etc)
SET(app_srcs rogue.cpp renderers/curses.cpp renderers/opengl.cpp)

# Pull in custom software libraries (appcore, tga, math)
include_directories("${CMAKE_SOURCE_DIR}/libs/appcore/include"
                    "${CMAKE_SOURCE_DIR}/libs/math/include")
set(LIBS ${LIBS} appcore tga math)

# Pull in required third party libraries (OpenGL, etc)
set(LIBS ${LIBS} ${GLUT_LIBRARIES} ${OpenGL_LIBRARIES} ${GLU_LIBRARY})
set(LIBS ${LIBS} ${CURSES_LIBRARY})

# Create a library that houses gameplay code (to seperate for use in tests)
add_library(rogue_engine STATIC ${game_srcs})

# Create the actual game executable that combines GUI and gameplay
add_executable(game ${app_srcs})
target_link_libraries(game rogue_engine ${LIBS})
