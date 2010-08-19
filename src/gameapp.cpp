#include "gameapp.h"
#include "renderers/opengl.h"
#include "octreeworld.h"

#include <vector>
#include <iostream>
#include <cassert>

#include <time.h>

using namespace Rogue;

std::vector<WorldCube> makeStressfulWorld();
std::vector<WorldCube> makeSimpleWorld( int rows, int cols, int depth );
std::vector<WorldCube> makeFirstWorld();

OctreeWorld * GWorld;

int rand( int min, int max )
{
    float base = rand() / ( RAND_MAX + 1.0 );
    int v = min + ( (max+1) * base  );

    return v;
}

void runGame()
{
    std::cout << "Creating game world 128x128x128" << std::endl;
    GWorld = new OctreeWorld( 128, 128, 128 );
    srand(time(NULL));

    std::cout << "Generating cubes for world" << std::endl;
    std::vector<WorldCube> cubes = makeSimpleWorld( 64, 64, 24 );

    std::cout << "Generated " << cubes.size() << " cubes" << std::endl;

    std::cout << "Populating cubes into world" << std::endl;
    for ( int i = 0; i < cubes.size(); ++i )
    {
        GWorld->put( cubes[i] );
    }

    std::cout << "Done!" << std::endl;
}

std::vector<WorldCube> makeFirstWorld()
{
    std::vector<WorldCube> cubes;

    // Make ground level all rock
    for ( int r = 0; r < 4; ++r )
    {
        for ( int c = 0; c < 4; ++c )
        {
            Point p( c, r, 0 );
            CubeData * data = new CubeData(Materials::Rock);
            cubes.push_back( WorldCube( p, data ) );
        }
    }

    // Make back wall level 1 also rock
    for ( int c = 0; c < 4; ++c )
    {
        Point p( c, 3, 1 );
        cubes.push_back( WorldCube( p, new CubeData(Materials::Rock) ) );
    }

        // Now make rest of level 1
    cubes.push_back(WorldCube(Point(1,0,1),new CubeData(Materials::Liquid)) );
    cubes.push_back(WorldCube(Point(2,0,1),new CubeData(Materials::Dirt)) );
    cubes.push_back(WorldCube(Point(3,0,1),new CubeData(Materials::Sand)) );
    
    cubes.push_back(WorldCube(Point(0,1,1),new CubeData(Materials::Grass)));
    cubes.push_back(WorldCube(Point(1,1,1),new CubeData(Materials::Water)));
    cubes.push_back(WorldCube(Point(2,1,1),new CubeData(Materials::Water)));
    cubes.push_back(WorldCube(Point(3,1,1),new CubeData(Materials::Sand)) );
    
    cubes.push_back(WorldCube(Point(0,2,1),new CubeData(Materials::Grass)));
    cubes.push_back(WorldCube(Point(1,2,1),new CubeData(Materials::Water)));
    cubes.push_back(WorldCube(Point(2,2,1),new CubeData(Materials::Water)));
    cubes.push_back(WorldCube(Point(3,2,1),new CubeData(Materials::Dirt)) );

    cubes.push_back(WorldCube(Point(0,0,2),new CubeData(Materials::Wood)));

    return cubes;
}

std::vector<WorldCube> makeStressfulWorld()
{
    std::vector<WorldCube> cubes;

    //
    // Stress test the game
    //
    int cubesToMake = rand( 2048*2, 2048*4 );
    int collision   = 0;

    std::cout << "Creating 128x128x128 world, populating "
              << cubesToMake << " cubes... ";

    for ( int i = 0; i < cubesToMake; ++i )
    {
        int r = rand( 0, 128 );
        int c = rand( 0, 128 );
        int d = rand( 0, 32 );

        Point p( c, r, d );

        // check for collision
        if (! GWorld->isEmptyAt( p ) )
        {
            collision++;
        }
        else
        {
            int t = rand( 0, 2 );
            Materials::Material m;

            if ( t == 0 ) { m = Materials::Rock; }
            if ( t == 1 ) { m = Materials::Grass; }
            if ( t == 2 ) { m = Materials::Water; }

            cubes.push_back( WorldCube( p, new CubeData(m) ) );
        }
    }

    std::cout << "done!" << std::endl;
    std::cout << "Added " << (cubesToMake-collision) << " cubes with "
              << collision << " collisions" << std::endl;

    return cubes;
}

std::vector<WorldCube> makeSimpleWorld( int rows, int cols, int depth )
{
    assert( depth > 12 );
    std::vector<WorldCube> cubes;

    int rockDepth = rand( 1, 3 );

    // make a rock ground
    for ( int d = 0; d < rockDepth; ++d )
    {
        for ( int r = 0; r < rows; ++r )
        {
            for ( int c = 0; c < cols; ++c )
            {
                cubes.push_back(WorldCube(Point(c,r,d), new CubeData(Materials::Rock)));
            }
        }
    }

    // make a grass floor
    for ( int r = 0; r < rows; ++r )
    {
        for ( int c = 0; c < cols; ++c )
        {
            cubes.push_back(WorldCube(Point(c,r,rockDepth),new CubeData(Materials::Grass)));
        }
    }

    // add random rocks
    int rocks = rand( 64, 1024 );

    for ( int i = 0; i < rocks; ++i )
    {
        int r = rand( 0, rows );
        int c = rand( 0, cols );
        int d = rockDepth + 2;
     
        cubes.push_back(WorldCube(Point(c,r,d),new CubeData(Materials::Wood)));
    }
    
    return cubes;
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
