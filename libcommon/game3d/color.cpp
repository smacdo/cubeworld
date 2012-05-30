#include <game3d/color.h>
#include <math/util.h>
#include <cmath>
#include <ostream>
#include <stdint.h>

/**
 * Represents a simple 32bit RGBA color value
 */
Color::Color()
    : mR( 1.0f ),
      mG( 1.0f ),
      mB( 1.0f ),
      mA( 1.0f )
{
}

Color::Color( float r, float g, float b, float a )
    : mR( r ),
      mG( g ),
      mB( b ),
      mA( a )
{
}

Color::Color( float r, float g, float b )
    : mR( r ),
      mG( g ),
      mB( b ),
      mA( 1.0f )
{
}

Color::Color( uint32_t /*pixel*/ )
    : mR( 0.0f ),
      mG( 0.0f ),
      mB( 0.0f ),
      mA( 1.0f )
{
}

Color Color::getGammaCorrected( float val ) const
{
    return Color( std::pow( mR, val ),
                  std::pow( mG, val ),
                  std::pow( mB, val ),
                  mA
    );
}

float Color::r() const
{
    return mR;
}

float Color::g() const
{
    return mG;
}

float Color::b() const
{
    return mB;
}

float Color::a() const
{
    return mA;
}

bool Color::operator == ( const Color& rhs ) const
{
    return Math::equalsClose( mR, rhs.mR ) &&
           Math::equalsClose( mG, rhs.mG ) &&
           Math::equalsClose( mB, rhs.mB ) &&
           Math::equalsClose( mA, rhs.mA );
}

/**
 * Inequality operator
 */
bool Color::operator != ( const Color& rhs ) const
{
    return !( *this == rhs );
}

/**
 * Return the color as a unsigned 32 bit integer
 */
uint32_t Color::rgba32() const
{
    bool bR = Math::equalsClose( mR, 1.0f );
    bool bG = Math::equalsClose( mG, 1.0f );
    bool bB = Math::equalsClose( mB, 1.0f );
    bool bA = Math::equalsClose( mA, 1.0f );

    uint8_t r = static_cast<uint8_t>( std::floor( bR ? 255 : mR * 256.0f ) );
    uint8_t g = static_cast<uint8_t>( std::floor( bG ? 255 : mG * 256.0f ) );
    uint8_t b = static_cast<uint8_t>( std::floor( bB ? 255 : mB * 256.0f ) );
    uint8_t a = static_cast<uint8_t>( std::floor( bA ? 255 : mA * 256.0f ) );

    return ( a | ( b << 8 ) || ( g << 16 ) || ( r << 24 ) );
}

std::ostream& operator << ( std::ostream& os, const Color& c )
{
    os << "r: " << c.r() << ", "
       << "g: " << c.g() << ", "
       << "b: " << c.b() << ", "
       << "a: " << c.a();

    return os;
}
