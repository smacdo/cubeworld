#include "gameapp.h"
#include "renderers/opengl.h"
#include "gameworld.h"
#include "cubeworld.h"
#include "cubedata.h"

#include <GL/freeglut.h>

#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>

#include <time.h>

using namespace Rogue;
World * GWorld;

void runGame()
{
    srand( static_cast<unsigned int>(time(NULL)) );
    GWorld = new World( 32, 32, 32 );

    std::cout << "Creating game world " 
              << GWorld->rows()  << "x"
              << GWorld->cols()  << "x"
              << GWorld->depth() << std::endl;

    makeSimpleWorld( *GWorld );

//    assert( GWorld->getCompiledMesh() != NULL );

    std::cout << "Created " << GWorld->cubeCount() << " cubes" << std::endl;
    std::cout << "Game is starting..." << std::endl;
}

void doGameTick( float , float  )
{
    assert( GWorld != NULL );
    renderScene( *GWorld );
}

void appExit( const std::string& message,
              const char * file,
              const char * func,
                    size_t line )
{
	appExit( message.c_str(), file, func, line );
}

void appExit( const char * message,
              const char * file,
              const char * func,
                    size_t line )
{
    std::cerr << std::endl;
    std::cerr << "============================== APPLICATION ERROR "
              << "==============================" << std::endl;
    std::cerr << " The application has encountered a fatal error, and"
              << " must exit. Error details"  << std::endl;
    std::cerr << " are listed below." << std::endl;
    std::cerr << std::endl;
    std::cerr << " MESSAGE: " << message << std::endl;
    std::cerr << " WHERE  : " << func    << ", line " << line
              << ", "         << file    << std::endl;
    std::cerr << "================================================="
              << "==============================" << std::endl;
    std::cerr << std::endl;

    exit(1);
}
