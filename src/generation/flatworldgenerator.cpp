/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "generation/flatworldgenerator.h"
#include "engine/material.h"
#include "engine/cubedata.h"
#include "engine/world.h"

#include <random>

FlatWorldGenerator::FlatWorldGenerator()
{
}

FlatWorldGenerator::~FlatWorldGenerator()
{
}

/**
 * Generates a flat world. A flat world has a bedrock layer, several
 * layers of dirt and stone topped off with grass
 */
World * FlatWorldGenerator::generate( unsigned int cols,
                                      unsigned int rows,
                                      unsigned int height,
                                      WorldView * pWorldView )
{
    const unsigned int GROUND_LEVELS = 5;

    // We need some randomness, now don't we?
    std::random_device rd;
    std::mt19937 rng( rd() );
    std::uniform_int_distribution<> dice( 0, 1 );

    // First create a new world object
    World * pWorld = new World( cols, rows, height, pWorldView );
    
    // 
    for ( unsigned int x = 0; x < cols; ++x )
    {
        for ( unsigned int z = 0; z < rows; ++z )
        {
            // bedrock at the bottom
            pWorld->put( CubeData( EMATERIAL_BEDROCK ), Point( x, 0, z ) );

            // now multiple in-between layers
            for ( unsigned int y = 0; y < GROUND_LEVELS; ++y )
            {
                EMaterialType m = ( dice(rng) == 0 ? EMATERIAL_GRASS :
                                                     EMATERIAL_ROCK );

                pWorld->put( CubeData( m ), Point( x, 1 + y, z ) );
            }

            // finally top it off with graaaaaassss
            pWorld->put( CubeData( EMATERIAL_GRASS ),
                         Point( x, 2 + GROUND_LEVELS, z ) );
        }
    }

    return pWorld;
}
