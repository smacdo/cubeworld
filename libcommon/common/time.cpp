#include <common/time.h>
#include <common/assert.h>

const double Time::TimeDelta = 0.000001;

/**
 * Default time constructor. Time is set to zero seconds.
 */
Time::Time()
    : mSeconds( 0.0 )
{
}

/**
 * Copy constructor
 */
Time::Time( const Time& t )
    : mSeconds( t.mSeconds )
{
}

/**
 * Value constructor
 */
Time::Time( int seconds )
    : mSeconds( seconds )
{
    assert( seconds >= 0 && "Time cannot consist of negative seconds" );
}

Time::Time( float seconds )
    : mSeconds( static_cast<double>(seconds) )
{
    assert( seconds >= 0.0f && "Time cannot consist of negative seconds" );
}

Time::Time( double seconds )
    : mSeconds( seconds )
{
    assert( seconds >= 0.0 && "Time cannot consist of negative seconds" );
}

Time& Time::operator = ( const Time& rhs )
{
    mSeconds = rhs.mSeconds;
    return *this;
}

bool Time::operator == ( const Time& rhs ) const
{
    return ( mSeconds + TimeDelta >= rhs.mSeconds &&
             mSeconds - TimeDelta <= rhs.mSeconds );
}

bool Time::operator != ( const Time& rhs ) const
{
    return !( *this == rhs );
}

Time Time::operator + ( const Time& rhs ) const
{
    return Time( mSeconds + rhs.mSeconds );
}

Time& Time::operator += ( const Time& rhs )
{
    mSeconds += rhs.mSeconds;
    return *this;
}

Time Time::operator - ( const Time& rhs ) const
{
    assert( mSeconds >= rhs.mSeconds );
    return Time( mSeconds - rhs.mSeconds );
}

Time& Time::operator -= ( const Time& rhs )
{
    assert( mSeconds >= rhs.mSeconds );
    
    mSeconds -= rhs.mSeconds;
    return *this;
}
