#include "gameapp.h"
#include "renderers/opengl.h"
#include "cubeworld.h"
#include "cubedata.h"

#include <vector>
#include <iostream>
#include <cassert>

#include <time.h>

using namespace Rogue;

void makeStressfulWorld( World& world );
void makeSimpleWorld( World& world );
void makeFlatWorld( World& world );

World * GWorld;

int rand( int min, int max )
{
    float base = rand() / ( RAND_MAX + 1.0 );
    int v = min + ( (max+1) * base  );

    return v;
}

void runGame()
{
    srand(time(NULL));
    GWorld = new World( 64, 64, 64 );

    std::cout << "Creating game world " 
              << GWorld->rows()  << "x"
              << GWorld->cols()  << "x"
              << GWorld->depth() << std::endl;

    makeSimpleWorld( *GWorld );

    std::cout << "Created " << GWorld->cubeCount() << " cubes" << std::endl;
    std::cout << "Game is starting..." << std::endl;
}

void makeFlatWorld( World& world )
{
    assert( world.depth() > 2 );

    // Make ground level all rock
    for ( int r = 0; r < world.rows(); ++r )
    {
        for ( int c = 0; c < world.cols(); ++c )
        {
            WorldCube wc( Point( c, r, 0 ),
                          new CubeData(Materials::Rock) );

            world.put( wc );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // Make a grass level
    for ( int r = 0; r < world.rows(); ++r )
    {
        for ( int c = 0; c < world.cols(); ++c )
        {
            WorldCube wc( Point( c, r, 1 ),
                          new CubeData(Materials::Grass) );

            world.put( wc );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    std::cout << std::endl;
}

void makeStressfulWorld( World& world )
{
    assert( world.depth() >= 10 );

    //
    // Stress test the game
    //
    for ( int r = 0; r < world.rows(); ++r )
    {
        for ( int c = 0; c < world.cols(); ++c )
        {
            int d = rand( 1, 10 );

            int t = rand( 0, 2 );
            Materials::Material m;

            if ( t == 0 ) { m = Materials::Rock; }
            if ( t == 1 ) { m = Materials::Grass; }
            if ( t == 2 ) { m = Materials::Water; }

            for ( int i = 0; i < d; ++i )
            {
                WorldCube wc( Point(c,r,i), new CubeData(m) );
                world.put( wc );
            }
        }

        if ( r % 8 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    std::cout << std::endl;
}

void makeSimpleWorld( World& world )
{
    int depth = world.depth();
    int rows  = world.rows();
    int cols  = world.cols();

    assert( depth > 8 );
    std::vector<WorldCube> cubes;

    // make a rock ground one layer deep
    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            WorldCube wc(WorldCube(Point(c,r,0), 
                         new CubeData(Materials::Rock)));
            world.put( wc );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // how about some dirt and rock in the middle?
    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            Materials::Material mat;
        
            if ( rand( 0, 1 ) == 0 )
            {
                mat = Materials::Dirt;
            }
            else
            {
                mat = Materials::Rock;
            }

            WorldCube wc(WorldCube(Point(c,r,1), 
                         new CubeData(mat)));
            world.put( wc );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // make a grass floor
    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            WorldCube wc( WorldCube( Point( c, r, 2 ),
                            new CubeData(Materials::Grass)));
            world.put( wc );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // add random rocks
    int rocks = rand( 128, 1024 );

    for ( int i = 0; i < rocks; ++i )
    {
        int r = rand( 0, rows );
        int c = rand( 0, cols );
        int d = rand( 0, 4 );

        for ( int j = 0; j < d; ++j )
        {
            WorldCube wc( WorldCube(Point(c,r,3+j),
                        new CubeData(Materials::Wood)));
            world.put( wc );
        }

        if ( i % 64 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    std::cout << std::endl;
}

void doGameTick( float deltaTime, float gameTime )
{
    assert( GWorld != NULL );

    renderScene( *GWorld );
}

void appExit( const char * message,
              const char * file,
              const char * func,
                    int    line )
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
