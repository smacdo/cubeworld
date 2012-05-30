#include "engine/cubedata.h"
#include <ostream>

CubeData::CubeData()
    : mMaterial( EMATERIAL_EMPTY )
{
}

CubeData::CubeData( EMaterialType material )
    : mMaterial( material )
{
}

CubeData::CubeData( const CubeData& cube )
    : mMaterial( cube.mMaterial )
{
}

CubeData& CubeData::operator = ( const CubeData& rhs )
{
    mMaterial = rhs.mMaterial;
    return *this;
}

bool CubeData::operator == ( const CubeData& rhs ) const
{
    return mMaterial == rhs.mMaterial;
}

bool CubeData::operator != ( const CubeData& rhs ) const
{
    return mMaterial != rhs.mMaterial;
}

void CubeData::setMaterial( EMaterialType material )
{
    mMaterial = material;
}

bool CubeData::isEmpty() const
{
    return mMaterial == EMATERIAL_EMPTY;
}

EMaterialType CubeData::materialType() const
{
    return mMaterial;
}

std::ostream& operator << ( std::ostream& os, const CubeData& cube )
{
    os << cube.materialType();
    return os;
}
