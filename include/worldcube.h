#ifndef SCOTT_ROGUELIKE_WORLDCUBE_H
#define SCOTT_ROGUELIKE_WORLDCUBE_H

#include "point.h"

namespace Rogue
{
    /**
    * Base materials for the game
    */
    namespace Materials
    {
        enum Material
        {
            None,
            Grass,
            Dirt,
            Water,
            Rock,
            Sand,
            Wood,
            Liquid
        };
    }
}

namespace Rogue
{

/**
 * Represents cube data
 */
class CubeData
{
public:
    CubeData()
    {
    }

    CubeData( const Materials::Material& material )
        : m_baseMaterial(material)
    {
    }

    CubeData( const CubeData& data )
        : m_baseMaterial( data.m_baseMaterial )
    {
    }

    const CubeData& operator = ( const CubeData& rhs )
    {
        m_baseMaterial = rhs.m_baseMaterial;
        return *this;
    }
    
    void setBaseMaterial( const Materials::Material& material )
    {
        m_baseMaterial = material;
    }

    Materials::Material baseMaterial() const { return m_baseMaterial; }

private:
    Materials::Material m_baseMaterial;
};


}

#endif
