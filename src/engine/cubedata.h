#ifndef SCOTT_CUBEWORLD_CUBEDATA_H
#define SCOTT_CUBEWORLD_CUBEDATA_H

#include <iosfwd>
#include "engine/material.h"

/**
 * Represents cube data
 */
class CubeData
{
public:
    // Constructor
    CubeData();

    // Constructor w/ matieral type
    CubeData( EMaterialType material );

    // Copy constructor
    CubeData( const CubeData& cube );

    // Assignment operator
    CubeData& operator = ( const CubeData& rhs );

    // Equality operator
    bool operator == ( const CubeData& rhs ) const;

    // Inequality operator
    bool operator != ( const CubeData& rhs ) const;
    
    // Set cube's material type
    void setMaterial( EMaterialType );

    // Check if material type is "empty"
    bool isEmpty() const;

    EMaterialType materialType() const;

private:
    EMaterialType mMaterial;
};

std::ostream& operator << ( std::ostream& os, const CubeData& cube );

#endif
