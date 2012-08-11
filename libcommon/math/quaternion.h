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
#ifndef SCOTT_MATH_QUATERNION_H
#define SCOTT_MATH_QUATERNION_H

#include <math/config.h>
#include <math/vector.h>

// Forward declarations
template<typename T> class TQuaternion;

template<typename T> T normal( const TQuaternion<T>& q );
template<typename T> TQuaternion<T> conjugate( const TQuaternion<T>& q );
template<typename T> TQuaternion<T> inverse( const TQuaternion<T>& q );
template<typename T> TQuaternion<T> normalize( const TQuaternion<T>& q );

/**
 * Quaternions are used to represent rotations in the game engine. Quaternions
 * are compact, do not suffer from gimbal lock and are easily interpolated.
 *
 * However, quaternions suffer from a significant downside - they are not
 * easily understood by looking at their value. The codebase is designed in
 * such a way that you should never need to manually create or read a
 * quaternion. Instead the user should simply use any number of utility
 * functions that can generate quarternions for you
 */
template<typename T>
class TQuaternion
{
public:
    // Public typedefs
    typedef T value_type;
    typedef value_type const const_value_type;
    typedef value_type& reference;
    typedef const_value_type& const_reference;
    typedef value_type* pointer;
    typedef const_value_type* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    /**
     * Quaternion default constructor
     */
    TQuaternion()
#ifdef MATH_DEBUG
        : mW( std::numeric_limits<T>::signaling_NaN() ),
          mX( std::numeric_limits<T>::signaling_NaN() ),
          mY( std::numeric_limits<T>::signaling_NaN() ),
          mZ( std::numeric_limits<T>::signaling_NaN() )
#endif
    {
    }

    /**
     * Quaternion constructor
     */
    TQuaternion( value_type w, value_type x, value_type y, value_type z )
        : mW( w ),
          mX( x ),
          mY( y ),
          mZ( z )
    {
    }

    /**
     * Copy constructor
     */
    TQuaternion( const TQuaternion<T>& q )
        : mW( q.mW ),
          mX( q.mX ),
          mY( q.mY ),
          mZ( q.mZ )
    {
    }

    /**
     * Assignment operator
     */
    TQuaternion<T>& operator =  ( const TQuaternion<T>& q )
    {
        mW = q.mW;
        mX = q.mX;
        mY = q.mY;
        mZ = q.mZ;

        return *this;
    }

    /**
     * Equality operator
     */
    bool operator == ( const TQuaternion<T>& q ) const
    {
        return Math::equalsClose( mW, q.mW ) &&
               Math::equalsClose( mX, q.mX ) &&
               Math::equalsClose( mY, q.mY ) &&
               Math::equalsClose( mZ, q.mZ );
    }

    /**
     * Inequality operator
     */
    bool operator != ( const TQuaternion& rhs ) const
    {
        return !( *this == rhs );
    }

    /**
     * Index operator
     */
    const_reference operator[]( unsigned int index ) const
    {
        MATH_ASSERT( index < 4, "Quaternion index out of range" );
        return *(&mW + index);
    }

    /**
     * Index operator
     */
    reference operator[]( unsigned int index )
    {
        MATH_ASSERT( index < 4, "Quaternion index out of range" );
        return *(&mW + index);
    }

    /**
     * Addition operator
     */
    TQuaternion<T> operator + ( const TQuaternion<T>& rhs ) const
    {
        return TQuaternion<T>(
                mW + rhs.mW,
                mX + rhs.mX,
                mY + rhs.mY,
                mZ + rhs.mZ
        );
    }

    /**
     * Self addition operator
     */
    TQuaternion<T>& operator += ( const TQuaternion<T>& rhs )
    {
        mW += rhs.mW;
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;

        return *this;
    }

    /**
     * Subtraction operator
     */
    TQuaternion<T> operator - ( const TQuaternion<T>& rhs ) const
    {
        return TQuaternion<T>(
                mW - rhs.mW,
                mX - rhs.mX,
                mY - rhs.mY,
                mZ - rhs.mZ
        );
    }

    /**
     * Self subtraction operator
     */
    TQuaternion<T>& operator -= ( const TQuaternion<T>& rhs )
    {
        mW -= rhs.mW;
        mX -= rhs.mX;
        mY -= rhs.mY;
        mZ -= rhs.mZ;

        return *this;
    }

    /**
     * Multiplication operator
     */
    TQuaternion<T> operator * ( const TQuaternion<T>& rhs ) const
    {
        return TQuaternion<T>(
                mW * rhs.mW - mX * rhs.mX - mY * rhs.mY - mZ * rhs.mZ,
                mW * rhs.mX + mX * rhs.mW + mY * rhs.mZ - mZ * rhs.mY,
                mW * rhs.mY + mY * rhs.mW + mZ * rhs.mX - mX * rhs.mZ,
                mW * rhs.mZ + mZ * rhs.mW + mX * rhs.mY - mY * rhs.mX
        );
    }

    /**
     * Self multiplication operator
     */
    TQuaternion<T>& operator *= ( const TQuaternion<T>& rhs )
    {
        value_type w = mW * rhs.mW - mX * rhs.mX - mY * rhs.mY - mZ * rhs.mZ;        
        value_type x = mW * rhs.mX + mX * rhs.mW + mY * rhs.mZ - mZ * rhs.mY;
        value_type y = mW * rhs.mY + mY * rhs.mW + mZ * rhs.mX - mX * rhs.mZ;
        value_type z = mW * rhs.mZ + mZ * rhs.mW + mX * rhs.mY - mY * rhs.mX;

        mW = w;
        mX = x;
        mY = y;
        mZ = z;

        return *this;
    }

    /**
     * Returns a vector3 of euler angles that are equivilant to this
     * quaternion in value
     */
    TVector3<T> eulerAngles() const
    {
        return TVector3<T>::IDENTITY;
    }

    /**
     * X component
     */
    value_type x() const
    {
        return mX;
    }

    /**
     * Y component
     */
    value_type y() const
    {
        return mY;
    }

    /**
     * Z component
     */
    value_type z() const
    {
        return mZ;
    }

    /**
     * W component
     */
    value_type w() const
    {
        return mW;
    }

    // Calculate the magnitude of a quaternion
    friend value_type normal<>( const TQuaternion<T>& q );

    // Calculate the conjugate of a quaternion
    friend TQuaternion<T> conjugate<>( const TQuaternion<T>& q );

    // Calculate the inverse of a quaternion
    friend TQuaternion<T> inverse<>( const TQuaternion<T>& q );

    // Normalize a quaternion
    friend TQuaternion<T> normalize<>( const TQuaternion<T>& q );

public:
    static const TQuaternion<T> ZERO;
    static const TQuaternion<T> IDENTITY;

private:
    value_type mW, mX, mY, mZ; 

private:
    friend class boost::serialization::access;

    /**
     * Serialization
     */
    template<typename Archive>
    void serialize( Archive& ar, const unsigned int version )
    {
        ar & mX & mY & mZ & mW;
    }
};

/**
 * Calculates and returns the normal of the quaternion
 *
 * TODO: Break this out into a .cpp to avoid the cmath include
 */
template<typename T>
T normal( const TQuaternion<T>& q )
{
    return( std::sqrt( q.mX * q.mX + q.mY * q.mY +
                       q.mZ * q.mZ + q.mW * q.mW ) );
}

/**
 * Calculates and returns the quaternion's conjugate
 */
template<typename T>
TQuaternion<T> conjugate( const TQuaternion<T>& q )
{
    return TQuaternion<T>( q.mW, -q.mX, -q.mY, -q.mZ );
}

/**
 * Calculates and returns the quaternion's inverse
 */
template<typename T>
TQuaternion<T> inverse( const TQuaternion<T>& q )
{
    return conjugate( q );
}

/**
 * Normalize a quaternion
 */
template<typename T>
TQuaternion<T> normalize( const TQuaternion<T>& q )
{
    T mag = normal( q );
    return TQuaternion<T>( q.mW / mag, q.mX / mag, q.mY / mag, q.mZ / mag );
}

/**
 * Console stream output
 */
template<typename T>
std::ostream& operator << ( std::ostream& os, const TQuaternion<T>& q )
{
    os << "{quat; "
       << "w: " << q.w() << ", "
       << "i: " << q.x() << ", "
       << "j: " << q.y() << ", "
       << "k: " << q.z()
       << "}";

    return os;
}

/**
 * Zero quaternion (all components are zero)
 */
template<typename T>
const TQuaternion<T> TQuaternion<T>::ZERO = TQuaternion<T>( 0, 0, 0, 0 );

/**
 * Identity quaternion
 */
template<typename T>
const TQuaternion<T> TQuaternion<T>::IDENTITY = TQuaternion<T>( 1, 0, 0, 0 );

#ifdef MATH_TYPEDEFS
typedef TQuaternion<scalar_t> Quat;
typedef TQuaternion<float> Quatf;
typedef TQuaternion<double> Quatd;
#endif

#endif
