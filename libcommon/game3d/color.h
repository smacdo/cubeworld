#ifndef SCOTT_COMMON_COLOR_H
#define SCOTT_COMMON_COLOR_H

#include <stdint.h>
#include <iosfwd>

/**
 * Represents a simple 32bit RGBA color value
 */
class Color
{
public:
    Color();
    Color( float r, float g, float b, float a );
    Color( float r, float g, float b );
    explicit Color( uint32_t pixel );

    Color getGammaCorrected( float val ) const;

    float r() const;
    float g() const;
    float b() const;
    float a() const;

    bool operator == ( const Color& rhs ) const;
    bool operator != ( const Color& rhs ) const;

    uint32_t rgba32() const;

private:
    float mR;
    float mG;
    float mB;
    float mA;
};

std::ostream& operator << ( std::ostream& os, const Color& c );

#endif
