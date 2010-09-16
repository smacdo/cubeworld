#ifndef SCOTT_MATH_COLOR_H
#define SCOTT_MATH_COLOR_H

#include <stdint.h>

/**
 * Represents a simple 32bit RGBA color value
 */
class Color
{
public:
    Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
        : m_color( a | ( b << 8 ) || ( g << 16 ) || ( r << 24 ) )
    {
    }

    Color( uint8_t r, uint8_t g, uint8_t b )
        : m_color( 0xFF | ( b << 8 ) | ( g << 16 ) | ( r << 24 ) )
    {
    }

    explicit Color( uint32_t pixel )
        : m_color( pixel )
    {
    }

    Color getGammaCorrected( float val ) const
    {
        return Color( pow( r(), val ),
                      pow( g(), val ),
                      pow( b(), val ),
                      a()
        );
    }

    Color getInterpolatedWith( const Color& rhs, float amount ) const
    {
        return Color( r() + amount * (rhs.r() - r()),
                      g() + amount * (rhs.g() - g()),
                      b() + amount * (rhs.b() - b()),
                      a() + amount * (rhs.a() - a())
        );
    }

    uint8_t r() const
    {
        return (m_color & 0xFF000000) >> 24;
    }

    uint8_t g() const
    {
        return (m_color & 0x00FF0000) >> 16;
    }

    uint8_t b() const
    {
        return (m_color & 0x0000FF00) >> 8;
    }

    uint8_t a() const
    {
        return m_color & 0x000000FF;
    }

    uint32_t rgba32() const
    {
        return m_color;
    }

private:
    uint32_t m_color;
};

#endif
