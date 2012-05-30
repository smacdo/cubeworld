#include <vector>
#include <limits>
#include <iostream>
#include "math/constants.h"

#include "engine/point.h"

float intersects( const Vec3& min,
                  const Vec3& max,
                  const Vec3& rayOrigin,
                  const Vec3& rayDir,
                        Vec3& surfaceNormal )
{
    // Surface normals lookup
    static Vec3 axes[3] = { Vec3( 1.0f, 0.0f, 0.0f ),
                            Vec3( 0.0f, 1.0f, 0.0f ),
                            Vec3( 0.0f, 0.0f, 1.0f ) };

    float tmin = std::numeric_limits<float>::min();
    float tmax = std::numeric_limits<float>::max();
    float t1, t2;

    char maxNormSet = 0, minNormSet = 0;

    Vec3 maxNormal, minNormal;

    // Intersect ray with x/y/z slabs
    for ( int k = 0; k < 3; ++k )
    {
        // check the ray against planes xk = -dx_k, xk = dx_k
        if ( rayDir[k] != 0.0f )
        {
            t1 = ( min[k] - rayOrigin[k] ) / rayDir[k];
            t2 = ( max[k] - rayOrigin[k] ) / rayDir[k];

            tmin = std::max( tmin, std::min( t1, t2 ) );
            tmax = std::min( tmax, std::max( t1, t2 ) );

            if ( t1 > Math::ZeroEpsilonF && tmin == t1 )  // -face
            {
                minNormal  = -axes[k];
                minNormSet = 1;
            }
            else if ( t2 > Math::ZeroEpsilonF && tmin == t2 ) // +face
            {
                minNormal  = axes[k];
                minNormSet = 1;
            }
            else if ( t1 > Math::ZeroEpsilonF && tmax == t1 ) // -face
            {
                maxNormal  = -axes[k];
                maxNormSet = 1;
            }
            else if ( t2 > Math::ZeroEpsilonF && tmax == t2 ) // +face
            {
                maxNormal  = -axes[k];
                maxNormSet = 1;
            }
        }
        else
        {
            if (( rayOrigin[k] < min[k] ) || ( rayOrigin[k] > max[k] ))
            {
                // not sure what happened here?
                //   out of bounds
                return std::numeric_limits<float>::infinity();
            }
        }
    }   // end for (axes...)

    // tmin..tmax now define the intersectino with parallelpiped
    if ( tmin >= tmax )
    {
        // intersection point is empty or a point
        //   (looks like the ray didn't even hit us)
        return std::numeric_limits<float>::infinity();
    }
    else if ( tmin > Math::ZeroEpsilonF )
    {
        if ( minNormSet != 1 )
        {
            std::cout << "tmin=" << tmin << ", tmax=" << tmax << std::endl;
            std::cout << "rd[0]=" << rayDir[0] << ", rd[1]=" << rayDir[1]
                      << ", rd[2]=" << rayDir[2] << std::endl;
            std::cout << "minNormSet=" << (int) minNormSet 
                      << ", maxNormSet=" << (int) maxNormSet << std::endl;
        }
        assert( minNormSet );
        surfaceNormal = minNormal;

        return tmin;
    }
    else if ( tmax > Math::ZeroEpsilonF )
    {
        assert( maxNormSet == 1 );
        surfaceNormal = maxNormal;

        return tmax;
    }
    else
    {
        // no hit
        return std::numeric_limits<float>::infinity();
    }
}

