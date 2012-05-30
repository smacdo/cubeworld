/*
 * Copyright 2010-2012 Scott MacDonald
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
#ifndef SCOTT_MATH_ANGLE_H
#define SCOTT_MATH_ANGLE_H

#include <math/config.h>
#include <math/util.h>

// Forward declaration
template<typename T> class Degrees;
template<typename T> class Radians;

/**
 * Represents an angle encoded in degrees
 */
template<typename T>
class Degrees
{
public:
    Degrees()
        : mValue( static_cast<T>(0) )
    {
    }

    explicit Degrees( T angle )
        : mValue( wrap( angle ) )
    {
    }

    Degrees( const Radians<T>& r )
        : mValue( r.as<T>() * Math::Rad2Deg )
    {
    }

    Degrees( const Degrees& d )
        : mValue( d.mValue )
    {
    }

    Degrees& operator = ( const Degrees& rhs )
    {
        mValue = rhs.mValue;
        return *this;
    }

    Degrees& operator = ( const Radians<T>& rhs )
    {
        mValue = rhs.as<T>() * Math::Rad2Deg;
        return *this;
    }

    bool operator == ( const Degrees& rhs ) const
    {
        return Math::equalsClose( mValue, rhs.mValue );
    }

    bool operator == ( const Radians<T>& rhs ) const
    {
        return Math::equalsClose( mValue, rhs.as<T>() * Math::Rad2Deg );
    }

    bool operator != ( const Degrees& rhs ) const
    {
        return (! Math::equalsClose( mValue, rhs.mValue ) );
    }

    bool operator != ( const Radians<T>& rhs ) const
    {
        return (! Math::equalsClose( mValue, rhs.as<T>() * Math::Rad2Deg ) );
    }

    template<typename U>
    U as() const
    {
        return static_cast<U>( mValue );
    }

private:
    T wrap( T v ) const
    {
        T a = std::fmod( v, static_cast<T>(360) );

        if ( a < static_cast<T>(0) )
        {
            a += static_cast<T>(360);
        }

        return a;
    }

private:
    T mValue;
};

/**
 * Represents an angle encoded in radians
 */
template<typename T>
class Radians
{
public:
    Radians()
        : mValue( static_cast<T>(0) )
    {
    }

    explicit Radians( T angle )
        : mValue( wrap( angle ) )
    {
    }

    Radians( const Degrees<T>& r )
        : mValue( r.as<T>() * Math::Deg2Rad )
    {
    }

    Radians( const Radians& d )
        : mValue( d.mValue )
    {
    }

    Radians& operator = ( const Radians& rhs )
    {
        mValue = rhs.mValue;
        return *this;
    }

    Radians& operator = ( const Degrees<T>& rhs )
    {
        mValue = rhs.as<T>() * Math::Deg2Rad;
        return *this;
    }

    bool operator == ( const Radians& rhs ) const
    {
        return Math::equalsClose( mValue, rhs.mValue );
    }

    bool operator == ( const Degrees<T>& rhs ) const
    {
        return Math::equalsClose( mValue, rhs.as<T>() * Math::Deg2Rad );
    }

    bool operator != ( const Radians& rhs ) const
    {
        return (! Math::equalsClose( mValue, rhs.mValue ) );
    }

    bool operator != ( const Degrees<T>& rhs ) const
    {
        return (! Math::equalsClose( mValue, rhs.as<T>() * Math::Deg2Rad ) );
    }

    template<typename U>
    U as() const
    {
        return static_cast<U>( mValue );
    }

private:
    T wrap( T v ) const
    {
        T a = std::fmod( v, static_cast<T>(Math::TwoPi) );

        if ( a < static_cast<T>(0) )
        {
            a += static_cast<T>(Math::TwoPi);
        }

        return a;
    }

private:
    T mValue;
};

#endif
