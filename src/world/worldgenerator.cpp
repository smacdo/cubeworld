#include "world/worldgenerator.h"
#include "engine/world.h"
#include "engine/cubedata.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

int rand( int min, int max )
{
    float base = static_cast<float>(rand() / ( RAND_MAX + 1.0 ));
    int v      = static_cast<int>( min + ( (max+1) * base  ) );

    return v;
}

void makeWorld( const char * type, World& world )
{
    if ( strcmp( type, "stressful" ) == 0 )
    {
        return makeStressfulWorld( world );
    }
    else if ( strcmp( type, "simple" ) == 0 )
    {
        return makeSimpleWorld( world );
    }
    else if ( strcmp( type, "flat" ) == 0 )
    {
        return makeFlatWorld( world );
    }
    else
    {
        return makeFlatWorld( world );
    }
}

void makeFlatWorld( World& world )
{
    assert( world.depth() > 2 );

    // Make ground level all rock
    for ( unsigned int r = 0; r < world.rows(); ++r )
    {
        for ( unsigned int c = 0; c < world.cols(); ++c )
        {
            world.put( CubeData( EMATERIAL_ROCK ), Point( c, r, 0 ) );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // Make a grass level
    for ( unsigned int r = 0; r < world.rows(); ++r )
    {
        for ( unsigned int c = 0; c < world.cols(); ++c )
        {
            world.put( CubeData( EMATERIAL_GRASS ), Point( c, r, 1 ) );
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
    for ( unsigned int r = 0; r < world.rows(); ++r )
    {
        for ( unsigned int c = 0; c < world.cols(); ++c )
        {
            int d = rand( 1, 10 );
            int t = rand( 0, 2 );

            EMaterialType m = EMATERIAL_EMPTY;

            if ( t == 0 ) { m = EMATERIAL_ROCK; }
            if ( t == 1 ) { m = EMATERIAL_GRASS; }
            if ( t == 2 ) { m = EMATERIAL_WATER; }

            for ( int i = 0; i < d; ++i )
            {
                world.put( CubeData( m ), Point( c, r, i ) );
            }
        }

        if ( r % 8 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    std::cout << std::endl;
}

void makeSimpleWorld( World& world )
{
    unsigned int rows  = world.rows();
    unsigned int cols  = world.cols();

    // make a rock ground one layer deep
    for ( unsigned int r = 0; r < rows; ++r )
    {
        for ( unsigned int c = 0; c < cols; ++c )
        {
            world.put( CubeData( EMATERIAL_ROCK ), Point( c, r, 0 ) );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // how about some dirt and rock in the middle?
    for ( unsigned int r = 0; r < rows; ++r )
    {
        for ( unsigned int c = 0; c < cols; ++c )
        {
            EMaterialType mat;
        
            if ( rand( 0, 1 ) == 0 )
            {
                mat = EMATERIAL_DIRT;
            }
            else
            {
                mat = EMATERIAL_ROCK;
            }

            world.put( CubeData( mat ), Point( c, r, 1 ) );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // make a grass floor
    for ( unsigned int r = 0; r < rows; ++r )
    {
        for ( unsigned int c = 0; c < cols; ++c )
        {
            world.put( CubeData( EMATERIAL_GRASS ), Point( c, r, 2 ) );
        }

        if ( r % 16 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    // add random rocks
    unsigned int rocks = rand( 128, 1024 );

    for ( unsigned int i = 0; i < rocks; ++i )
    {
        unsigned int r = rand( 0, rows );
        unsigned int c = rand( 0, cols );
        unsigned int d = rand( 0, 4 );

        for ( unsigned int j = 0; j < d; ++j )
        {
            world.put( CubeData( EMATERIAL_WOOD ), Point( c, r, 3 + j ) );
        }

        if ( i % 64 == 0 ) { std::cout << "-"; std::cout.flush(); }
    }

    std::cout << std::endl;
}

