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
#ifndef SCOTT_MATH_VECTOR_H
#define SCOTT_MATH_VECTOR_H

#include <math/config.h>
#include <math/util.h>
#include <math/constants.h>
#include <ostream>

/////////////////////////////////////////////////////////////////////////////
// Forward declarations
//  - Need to forward declare all of our vector functions because C++ is
//    incapable of understanding a friend decalartion without already having
//    the function definition
/////////////////////////////////////////////////////////////////////////////
template<typename T> class TVector4;
template<typename T> class TVector3;
template<typename T> class TVector2;

namespace boost { namespace serialization { class access; } }

template<typename T> T dot( const TVector3<T>& lhs, const TVector3<T>& rhs );
template<typename T> TVector3<T> cross( const TVector3<T>& lhs, const TVector3<T>& rhs );
template<typename T> T length( const TVector4<T>& v );
template<typename T> T length( const TVector3<T>& v );
template<typename T> T length( const TVector2<T>& v );
template<typename T> T lengthSquared( const TVector4<T>& v );
template<typename T> T lengthSquared( const TVector3<T>& v );
template<typename T> T lengthSquared( const TVector2<T>& v );
template<typename T> TVector4<T> normalized( const TVector4<T>& v );
template<typename T> TVector3<T> normalized( const TVector3<T>& v );
template<typename T> TVector2<T> normalized( const TVector2<T>& v );
template<typename T> TVector3<T> rotateAroundX( const TVector3<T>& v, T angle );
template<typename T> TVector3<T> rotateAroundY( const TVector3<T>& v, T angle );
template<typename T> TVector3<T> rotateAroundZ( const TVector3<T>& v, T angle );
template<typename T> TVector3<T> rotateAround( const TVector3<T>& v,
                                               const TVector3<T>& axis,
                                               T angle );
                                                
template<typename T> T angleBetween( const TVector3<T>& lhs,
                                     const TVector3<T>& rhs );

/**
 * Generic templated vector4 class. Stores four values that are packed together
 * in memory as XYZW with no extra padding.
 *
 * Vector4 contains all basic operators expected of a Vector4 class, and
 * contains non-member functions for performing operations on the class. All of
 * these methods and functions conform to expected mathematical rules regarding
 * vector math.
 */
template<typename T>
class TVector4
{
public:
    // Type traits
    typedef T value_type;
    typedef value_type const const_value_type;
    typedef value_type& reference;
    typedef const_value_type& const_reference;
    typedef value_type* pointer;
    typedef const_value_type* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // The zero vector
    const static TVector4<T> ZERO;

    // Defines how many values are stored in a vector4 instance
    enum { NUM_COMPONENTS = 4 };

    /**
     * Standard vector constructor. Follows C++ standards of not
     * initializing basic value types, so do not assume the vector
     * is created with values set to zero.
     *
     * If you need a zero vector, call the static method ::ZeroVector()
     */
    TVector4()
#ifdef MATH_DEBUG
        : mX( std::numeric_limits<T>::signaling_NaN() ),
          mY( std::numeric_limits<T>::signaling_NaN() ),
          mZ( std::numeric_limits<T>::signaling_NaN() ),
          mW( std::numeric_limits<T>::signaling_NaN() )
#endif
    {
    }

    /**
     * Copy-initialize vector from a pointer to an array of values.
     * This constructor expects that the passed array contains at 
     * least four values, but there is nothing to check this constraint
     */
    explicit TVector4( const_pointer pVals )
        : mX( pVals[0] ), mY( pVals[1] ), mZ( pVals[2] ), mW( pVals[3] )
    {
    }

    /**
     * Vector x/y/z constructor. Takes the provided x/y/z values and
     * assigns it to the newly constructed vector.
     */
    TVector4( value_type x, value_type y, value_type z, value_type w )
        : mX( x ), mY( y ), mZ( z ), mW( w )
    {
    }

    /**
     * Copy constructor
     */
    TVector4( const TVector4<T>& v )
        : mX( v.mX ), mY( v.mY ), mZ( v.mZ ), mW( v.mW )
    {
    }

    /**
     * Read-only index operator, used to read one of the vector's four
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 3)
     * \return        Value of the component in the vector
     */
    const_reference operator [] ( unsigned int index ) const
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Vector index operator, used to read one of the vector's four
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 3)
     * \return        Value of the component in the vector
     */
    reference operator [] ( unsigned int index )
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Returns a pointer to the first element in the vector. Useful for
     * when a legacy API takes a 4D vector as a T*
     */
    pointer ptr()
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 4D vector as a const T*
     */
    const_pointer ptr() const
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 4D vector as a const T*
     */
    const_pointer const_ptr() const
    {
        return &mX;
    }

    /**
     * Assignment operator. Copy values from the right hand side and assign
     * it to this vector
     */
    TVector4<T>& operator = ( const TVector4<T>& rhs )
    {
        mX = rhs.mX;
        mY = rhs.mY;
        mZ = rhs.mZ;
        mW = rhs.mW;

        return *this;
    }

    /**
     * Equality operator
     */
    bool operator == ( const TVector4<T>& rhs ) const
    {
#ifdef MATH_FUZZY_EQUALS
    return ( Math::equalsClose( mX, rhs.mX ) &&
             Math::equalsClose( mY, rhs.mY ) &&
             Math::equalsClose( mZ, rhs.mZ ) &&
             Math::equalsClose( mW, rhs.mW ) );
#else
    return ( mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ && mW = rhs.mW );
#endif
    }

    /**
     * Inequality operator
     */
    bool operator != ( const TVector4<T>& rhs ) const
    {
        return !( *this == rhs );
    }

    /**
     * Unary negation operator. Negates all components of the value, which is
     * the same as multiplying all components by -1.0.
     */
    friend TVector4<T> operator - ( const TVector4<T>& rhs )
    {
        return TVector4( -rhs.mX, -rhs.mY, -rhs.mZ, -rhs.mW );
    }

    /**
     * Component wise addition operator
     */
    friend TVector4<T> operator + ( const TVector4<T>& lhs,
                                    const TVector4<T>& rhs )
    {
        return TVector4( lhs.mX + rhs.mX,
                         lhs.mY + rhs.mY,
                         lhs.mZ + rhs.mZ,
                         lhs.mW + rhs.mW );
    }

    /**
     * Component wise subtraction operator
     */
    friend TVector4<T> operator - ( const TVector4<T>& lhs,
                                    const TVector4<T>& rhs )
    {
        return TVector4<T>( lhs.mX - rhs.mX,
                            lhs.mY - rhs.mY,
                            lhs.mZ - rhs.mZ,
                            lhs.mW - rhs.mW );
    }

    /**
     * Vector multiplication operator. Scales the vector by the given scalar,
     * which is identical to multiplying all of the vector's components by the
     * scalar.
     */
    friend TVector4<T> operator * ( const TVector4<T>& lhs, 
                                    value_type scalar )
    {
        return TVector4( lhs.mX * scalar, 
                         lhs.mY * scalar, 
                         lhs.mZ * scalar,
                         lhs.mW * scalar );
    }

    /**
     * Vector division operator. Scales the vector by the inverse of the given
     * scalar, which is identical to dividing all of the vector's components by
     * the scalar.
     */
    friend TVector4<T> operator / ( const TVector4<T>& lhs,
                                    value_type scalar )

    {
        return TVector4( lhs.mX / scalar,
                         lhs.mY / scalar,
                         lhs.mZ / scalar,
                         lhs.mW / scalar );
    }


    /**
     * Component wise self addition operator
     */
    TVector4<T>& operator += ( const TVector4<T>& rhs )
    {
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;
        mW += rhs.mW;

        return *this;
    }

    /**
     * Component wise self subtraction operator
     */
    TVector4<T>& operator -= ( const TVector4<T>& rhs )
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        mZ -= rhs.mZ;
        mW -= rhs.mW;

        return *this;
    }

    /**
     * Component wise scalar self multiplication operator
     */
    TVector4<T>& operator *= ( value_type rhs )
    {
        mX *= rhs;
        mY *= rhs;
        mZ *= rhs;
        mW *= rhs;

        return *this;
    }

    /**
     * Component wise scalar self division operator
     */
    TVector4<T>& operator /= ( value_type rhs )
    {
        mX /= rhs;
        mY /= rhs;
        mZ /= rhs;
        mW /= rhs;

        return *this;
    }

    /**
     * Return the value of the vector's X component
     */
    inline value_type x() const
    {
        return mX;
    }

    /**
     * Return the value of the vector's Y component
     */
    inline value_type y() const
    {
        return mY;
    }

    /**
     * Return the value of the vector's Z component
     */
    inline value_type z() const
    {
        return mZ;
    }

    /**
     * Return the value of the vector's W component
     */
    inline value_type w() const
    {
        return mW;
    }

    // Returns the length (magnitude) of this vector
    friend value_type length<>( const TVector4<T>& v );

    // Returns the length squared of this vector
    friend value_type lengthSquared<>( const TVector4<T>& v );

    // Returns normalized version of this vector
    friend TVector4<T> normalized<>( const TVector4<T>& v );

private:
    union
	{
		struct { value_type mX, mY, mZ, mW; };
		struct { value_type v[NUM_COMPONENTS]; };
	};

private:
    friend class boost::serialization::access;
    
    /**
     * Serialization
     */
    template<typename Archive>
    void serialize( Archive& ar, const unsigned int /*version*/ )
    {
        ar & mX & mY & mZ & mW;
    }
};

/**
 * Generic templated vector3 class. Contains three values that are packed
 * together in memory, and an array of vectors should store these component
 * values linearly in memory with no extra padding.
 *
 * Vector3 contains all basic operators expected of a Vector3 class, and
 * contains non-member functions for performing operations on the class. All of
 * these methods and functions conform to expected mathematical rules regarding
 * vector math.
 */
template<typename T>
class TVector3
{
public:
    // Type traits
    typedef T value_type;
    typedef value_type const const_value_type;
    typedef value_type& reference;
    typedef const_value_type& const_reference;
    typedef value_type* pointer;
    typedef const_value_type* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // Zero vector
    const static TVector3<T> ZERO;

    /// Defines how many values are stored in a vector3 instance
    enum { NUM_COMPONENTS = 3 };

    /**
     * Standard vector constructor. Follows C++ standards of not
     * initializing basic value types, so do not assume the vector
     * is created with values set to zero.
     *
     * If you need a zero vector, call the static method ::ZeroVector()
     */
    TVector3()
#ifdef MATH_DEBUG
        : mX( std::numeric_limits<T>::signaling_NaN() ),
          mY( std::numeric_limits<T>::signaling_NaN() ),
          mZ( std::numeric_limits<T>::signaling_NaN() )
#endif
    {
    }

    /**
     * Copy-initialize vector from a pointer to an array of values.
     * This constructor expects that the passed array contains at 
     * least four values, but there is nothing to check this constraint
     */
    explicit TVector3( const_pointer pVals )
        : mX( pVals[0] ), mY( pVals[1] ), mZ( pVals[2] )
    {
    }

    /**
     * Vector x/y/z constructor. Takes the provided x/y/z values and
     * assigns it to the newly constructed vector.
     */
    TVector3( value_type x, value_type y, value_type z )
        : mX( x ), mY( y ), mZ( z )
    {
    }

    /**
     * Copy constructor
     */
    TVector3( const TVector3<T>& v )
        : mX( v.mX ), mY( v.mY ), mZ( v.mZ )
    {
    }

    /**
     * Read-only index operator, used to read one of the vector's three 
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 2)
     * \return        Value of the component in the vector
     */
    const_reference operator [] ( unsigned int index ) const
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Vector index operator, used to read one of the vector's three
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 2)
     * \return        Value of the component in the vector
     */
    reference operator [] ( unsigned int index )
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Returns a pointer to the first element in the vector. Useful for
     * when a legacy API takes a 3D vector as a T*
     */
    pointer ptr()
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 3D vector as a const T*
     */
    const_pointer ptr() const
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 4D vector as a const T*
     */
    const_pointer const_ptr() const
    {
        return &mX;
    }
    /**
     * Assignment operator. Copy values from the right hand side and assign
     * it to this vector
     */
    TVector3<T>& operator = ( const TVector3<T>& rhs )
    {
        mX = rhs.mX;
        mY = rhs.mY;
        mZ = rhs.mZ;

        return *this;
    }

    /**
     * Equality operator
     */
    bool operator == ( const TVector3<T>& rhs ) const
    {
#ifdef MATH_FUZZY_EQUALS
    return ( Math::equalsClose( mX, rhs.mX ) &&
             Math::equalsClose( mY, rhs.mY ) &&
             Math::equalsClose( mZ, rhs.mZ ) );
#else
    return ( mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ );
#endif
    }

    /**
     * Inequality operator
     */
    bool operator != ( const TVector3<T>& rhs ) const
    {
        return !( *this == rhs );
    }

    /**
     * Unary negation operator. Negates all components of the value, which is
     * the same as multiplying all components by -1.0.
     */
    friend TVector3<T> operator - ( const TVector3<T>& rhs )
    {
        return TVector3( -rhs.mX, -rhs.mY, -rhs.mZ );
    }

    /**
     * Component wise addition operator
     */
    friend TVector3<T> operator + ( const TVector3<T>& lhs,
                                    const TVector3<T>& rhs )
    {
        return TVector3( lhs.mX + rhs.mX,
                         lhs.mY + rhs.mY,
                         lhs.mZ + rhs.mZ );
    }

    /**
     * Component wise subtraction operator
     */
    friend TVector3<T> operator - ( const TVector3<T>& lhs,
                                    const TVector3<T>& rhs )
    {
        return TVector3<T>( lhs.mX - rhs.mX,
                            lhs.mY - rhs.mY,
                            lhs.mZ - rhs.mZ );
    }

    /**
     * Vector multiplication operator. Scales the vector by the given scalar,
     * which is identical to multiplying all of the vector's components by the
     * scalar value.
     */
    friend TVector3<T> operator * ( const TVector3<T>& lhs, 
                                    value_type scalar )
    {
        return TVector3( lhs.mX * scalar, 
                         lhs.mY * scalar, 
                         lhs.mZ * scalar );
    }

    /**
     * Vector division operator. Scales the vector by the inverse of the given
     * scalar, which is identical to dividing all of the vector's components by
     * the scalar value.
     */
    friend TVector3<T> operator / ( const TVector3<T>& lhs,
                                    value_type scalar )

    {
        return TVector3( lhs.mX / scalar,
                         lhs.mY / scalar,
                         lhs.mZ / scalar );
    }

    /**
     * Component wise self addition operator
     */
    TVector3<T>& operator += ( const TVector3<T>& rhs )
    {
        mX += rhs.mX;
        mY += rhs.mY;
        mZ += rhs.mZ;

        return *this;
    }

    /**
     * Component wise self subtraction operator
     */
    TVector3<T>& operator -= ( const TVector3<T>& rhs )
    {
        mX -= rhs.mX;
        mY -= rhs.mY;
        mZ -= rhs.mZ;

        return *this;
    }

    /**
     * Component wise scalar self multiplication operator
     */
    TVector3<T>& operator *= ( value_type rhs )
    {
        mX *= rhs;
        mY *= rhs;
        mZ *= rhs;

        return *this;
    }

    /**
     * Component wise scalar self division operator
     */
    TVector3<T>& operator /= ( value_type rhs )
    {
        mX /= rhs;
        mY /= rhs;
        mZ /= rhs;

        return *this;
    }

    /**
     * Return the value of the vector's X component
     */
    inline value_type x() const
    {
        return mX;
    }

    /**
     * Return the value of the vector's Y component
     */
    inline value_type y() const
    {
        return mY;
    }

    /**
     * Return the value of the vector's Z component
     */
    inline value_type z() const
    {
        return mZ;
    }

    /**
     * Rotates the vector around the X axis, and returns the result
     * of this rotation
     */
    friend TVector3<T> rotateAroundX<>( const TVector3<T>& v,
                                        value_type angle );

    /**
     * Rotates the vector around the Y axis, and returns the result
     * of this rotation
     */
    friend TVector3<T> rotateAroundY<>( const TVector3<T>& v,
                                        value_type angle );

    /**
     * Rotates the vector around the Z axis, and returns the result
     * of the rotation
     */
    friend TVector3<T> rotateAroundZ<>( const TVector3<T>& v,
                                        value_type angle );

    /**
     * Rotate around an arbitrary axis. We can easily accomplish
     * this with a matrix, however for the sake of not depending on a
     * matrix implementation we'll fake it
     */
    friend TVector3<T> rotateAround<>( const TVector3<T>& v,
                                       const TVector3<T>& axis,
                                       value_type angle );

    /**
     * Cross product. Returns the result of crossing the lhs vector with
     * the rhs vector
     */
    friend TVector3<T> cross<>( const TVector3<T>& lhs,
                                const TVector3<T>& rhs );

    /**
     * Dot product. Returns the result of dotting the lhs vector with the 
     * rhs vector
     */
    friend value_type dot<>( const TVector3<T>& lhs, const TVector3<T>& rhs );

    /**
     * Returns the angle between the lhs vector and the rhs vector
     */
    friend value_type angleBetween<>( const TVector3<T>& lhs,
                                      const TVector3<T>& rhs );

    /**
     * Returns the length (magnitude) of the vector
     */
    friend value_type length<>( const TVector3<T>& v );

    /**
     * Returns the length squared of the vector (no sqrt)
     */
    friend value_type lengthSquared<>( const TVector3<T>& v );

    /**
     * Returns a normalized verison of this vector
     */
    friend TVector3<T> normalized<>( const TVector3<T>& v );

private:
    union
	{
		struct { value_type mX, mY, mZ; };
		struct { value_type v[NUM_COMPONENTS]; };
	};

private:
    friend class boost::serialization::access;
    
    /**
     * Serialization
     */
    template<typename Archive>
    void serialize( Archive& ar, const unsigned int /*version*/ )
    {
        ar & mX & mY & mZ;
    }
};

/**
 * Generic templated vector2 class. Stores two values that are packed together
 * in memory as XY with no extra padding.
 *
 * Vector2 contains all basic operators expected of a Vector2 class, and
 * contains non-member functions for performing operations on the class. All of
 * these methods and functions conform to expected mathematical rules regarding
 * vector math.
 */
template<typename T>
class TVector2
{
public:
    // Type traits
    typedef T value_type;
    typedef value_type const const_value_type;
    typedef value_type& reference;
    typedef const_value_type& const_reference;
    typedef value_type* pointer;
    typedef const_value_type* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // Zero vector
    const static TVector2<T> ZERO;

    // Defines how many values are stored in a vector2 instance
    enum { NUM_COMPONENTS = 2 };

    /**
     * Standard vector constructor. Follows C++ standards of not
     * initializing basic value types, so do not assume the vector
     * is created with values set to zero.
     *
     * If you need a zero vector, call the static method ::ZeroVector()
     */
    TVector2()
#ifdef MATH_DEBUG
        : mX( std::numeric_limits<T>::signaling_NaN() ),
          mY( std::numeric_limits<T>::signaling_NaN() )
#endif
    {
    }

    /**
     * Copy-initialize vector from a pointer to an array of values.
     * This constructor expects that the passed array contains at 
     * least four values, but there is nothing to check this constraint
     */
    explicit TVector2( const_pointer pVals )
        : mX( pVals[0] ), mY( pVals[1] )
    {
    }

    /**
     * Vector x/y constructor. Takes the provided x/y values and
     * assigns it to the newly constructed vector.
     */
    TVector2( value_type x, value_type y )
        : mX( x ), mY( y )
    {
    }

    /**
     * Copy constructor
     */
    TVector2( const TVector2<T>& v )
        : mX( v.mX ), mY( v.mY )
    {
    }

    /**
     * Read-only index operator, used to read one of the vector's three
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 1)
     * \return        Value of the component in the vector
     */
    const_reference operator [] ( unsigned int index ) const
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Vector index operator, used to read one of the vector's three
     * cardinal axis values
     *
     * \param  index  The vector's component index (0 to 1)
     * \return        Value of the component in the vector
     */
    reference operator [] ( unsigned int index )
    {
        ASSERT_MSG( index < NUM_COMPONENTS, "Vector operator[] out of range" );
        return v[index];
    }

    /**
     * Returns a pointer to the first element in the vector. Useful for
     * when a legacy API takes a 2D vector as a T*
     */
    pointer ptr()
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 2D vector as a const T*
     */
    const_pointer ptr() const
    {
        return &mX;
    }

    /**
     * Returns a constant pointer to the first element in the vector. Useful
     * for when a legacy API takes a 2D vector as a const T*
     */
    const_pointer const_ptr() const
    {
        return &mX;
    }

    /**
     * Assignment operator. Copy values from the right hand side and assign
     * it to this vector
     */
    TVector2<T>& operator = ( const TVector2<T>& rhs )
    {
        mX = rhs.mX;
        mY = rhs.mY;

        return *this;
    }

    /**
     * Equality operator
     */
    bool operator == ( const TVector2<T>& rhs ) const
    {
#ifdef MATH_FUZZY_EQUALS
    return ( Math::equalsClose( mX, rhs.mX ) &&
             Math::equalsClose( mY, rhs.mY ) );
#else
    return ( mX == rhs.mX && mY == rhs.mY );
#endif
    }

    /**
     * Inequality operator
     */
    bool operator != ( const TVector2<T>& rhs ) const
    {
        return !( *this == rhs );
    }

    /**
     * Unary negation operator. Negates all components of the value, which is
     * the same as multiplying all components by -1.0.
     */
    friend TVector2<T> operator - ( const TVector2<T>& rhs )
    {
        return TVector2( -rhs.mX, -rhs.mY );
    }

    /**
     * Component wise addition operator
     */
    friend TVector2<T> operator + ( const TVector2<T>& lhs,
                                    const TVector2<T>& rhs )
    {
        return TVector2( lhs.mX + rhs.mX,
                         lhs.mY + rhs.mY );
    }

    /**
     * Component wise subtraction operator
     */
    friend TVector2<T> operator - ( const TVector2<T>& lhs,
                                    const TVector2<T>& rhs )
    {
        return TVector2<T>( lhs.mX - rhs.mX,
                            lhs.mY - rhs.mY );
    }

    /**
     * Vector multiplication operator. Scales the vector by the given scalar,
     * which is identical to multiplying all of the vector's components by the
     * scalar.
     */
    friend TVector2<T> operator * ( const TVector2<T>& lhs, 
                                    value_type scalar )
    {
        return TVector2( lhs.mX * scalar, 
                         lhs.mY * scalar );
    }

    /**
     * Vector division operator. Scales the vector by the inverse of the given
     * scalar, which is identical to dividing all of the vector's components by
     * the scalar.
     */
    friend TVector2<T> operator / ( const TVector2<T>& lhs,
                                    value_type scalar )

    {
        return TVector2( lhs.mX / scalar,
                         lhs.mY / scalar );
    }


    /**
     * Component wise self addition operator
     */
    TVector2<T>& operator += ( const TVector2<T>& rhs )
    {
        mX += rhs.mX;
        mY += rhs.mY;

        return *this;
    }

    /**
     * Component wise self subtraction operator
     */
    TVector2<T>& operator -= ( const TVector2<T>& rhs )
    {
        mX -= rhs.mX;
        mY -= rhs.mY;

        return *this;
    }

    /**
     * Component wise scalar self multiplication operator
     */
    TVector2<T>& operator *= ( value_type rhs )
    {
        mX *= rhs;
        mY *= rhs;

        return *this;
    }

    /**
     * Component wise scalar self division operator
     */
    TVector2<T>& operator /= ( value_type rhs )
    {
        mX /= rhs;
        mY /= rhs;

        return *this;
    }

    /**
     * Return the value of the vector's X component
     */
    inline value_type x() const
    {
        return mX;
    }

    /**
     * Return the value of the vector's Y component
     */
    inline value_type y() const
    {
        return mY;
    }

    /**
     * Returns the length (magnitude) of this vector.
     */
    friend value_type length<>( const TVector2<T>& v );

    /**
     * Returns the length squared of the vector (no sqrt)
     */
    friend value_type lengthSquared<>( const TVector2<T>& v );

    /**
     * Returns a normalized version of this vector
     */
    friend TVector2<T> normalized<>( const TVector2<T>& v );

private:
    union
	{
		struct { value_type mX, mY; };
		struct { value_type v[NUM_COMPONENTS]; };
	};

private:
    friend class boost::serialization::access;
    
    /**
     * Serialization
     */
    template<typename Archive>
    void serialize( Archive& ar, const unsigned int /*version*/ )
    {
        ar & mX & mY;
    }
};

/////////////////////////////////////////////////////////////////////////////
// Vector static definitions
/////////////////////////////////////////////////////////////////////////////
template<typename T>
const TVector4<T> TVector4<T>::ZERO = TVector4<T>( 0, 0, 0, 0 );

template<typename T>
const TVector3<T> TVector3<T>::ZERO = TVector3<T>( 0, 0, 0 );

template<typename T>
const TVector2<T> TVector2<T>::ZERO = TVector2<T>( 0, 0 );

/////////////////////////////////////////////////////////////////////////////
// Templated vector method definitions
/////////////////////////////////////////////////////////////////////////////
template<typename T>
TVector3<T> cross ( const TVector3<T>& lhs,
                    const TVector3<T>& rhs )
{
    return TVector3<T>( lhs.mY * rhs.mZ - lhs.mZ * rhs.mY,
                        lhs.mZ * rhs.mX - lhs.mX * rhs.mZ,
                        lhs.mX * rhs.mY - lhs.mY * rhs.mX );
}

template<typename T>
T dot ( const TVector3<T>& lhs, const TVector3<T>& rhs )
{
    return lhs.mX * rhs.mX + lhs.mY * rhs.mY + lhs.mZ * rhs.mZ;
}

template<typename T> T angleBetween( const TVector3<T>& lhs, const TVector3<T>& rhs );
template<> float angleBetween( const TVector3<float>& lhs, const TVector3<float>& rhs );

template<typename T> T length( const TVector4<T>& v );  // must specialize
template<> float length( const TVector4<float>& v );

template<typename T> T length( const TVector3<T>& v ); // must specialize
template<> float length( const TVector3<float>& v );

template<typename T> T length( const TVector2<T>& v );  // must specialize
template<> float length( const TVector2<float>& v );

template<typename T>
T lengthSquared( const TVector4<T>& v )
{
    return v.mX * v.mX + v.mY * v.mY + v.mZ * v.mZ + v.mW * v.mW;
}

template<typename T>
T lengthSquared( const TVector3<T>& v )
{
    return v.mX * v.mX + v.mY * v.mY + v.mZ * v.mZ;
}

template<typename T>
T lengthSquared( const TVector2<T>& v )
{
    return v.mX * v.mX + v.mY * v.mY;
}

template<typename T> TVector4<T> normalized( const TVector4<T>& v );
template<> TVector4<float> normalized( const TVector4<float>& v );

template<typename T> TVector3<T> normalized( const TVector3<T>& v );
template<> TVector3<float> normalized( const TVector3<float>& v );

template<typename T> TVector2<T> normalized( const TVector2<T>& v );
template<> TVector2<float> normalized( const TVector2<float>& v );

template<typename T> TVector3<T> rotateAroundX( const TVector3<T>& v, T angle );
template<> TVector3<float> rotateAroundX( const TVector3<float>& v, float angle );

template<typename T> TVector3<T> rotateAroundY( const TVector3<T>& v, T angle );
template<> TVector3<float> rotateAroundY( const TVector3<float>& v, float angle );

template<typename T> TVector3<T> rotateAroundZ( const TVector3<T>& v, T angle );
template<> TVector3<float> rotateAroundZ( const TVector3<float>& v, float angle );

template<typename T> TVector3<T> rotateAround( const TVector3<T>& v,
                                               const TVector3<T>& axis,
                                               T angle );
template<> TVector3<float> rotateAround( const TVector3<float>& v,
                                         const TVector3<float>& axis,
                                         float angle );

template<typename T>
std::ostream& operator << ( std::ostream& os, const TVector4<T>& v )
{
    os << "<"
       << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w()
       << ">";
    return os;
}


template<typename T>
std::ostream& operator << ( std::ostream& os, const TVector3<T>& v )
{
    os << "<" << v.x() << ", " << v.y() << ", " << v.z() << ">";
    return os;
}

template<typename T>
std::ostream& operator << ( std::ostream& os, const TVector2<T>& v )
{
    os << "<"
       << v.x() << ", " << v.y()
       << ">";
    return os;
}

/////////////////////////////////////////////////////////////////////////////
// Vector typedefs - typedef common vector types
/////////////////////////////////////////////////////////////////////////////
#ifdef MATH_TYPEDEFS
typedef TVector4<scalar_t> Vec4;
typedef TVector4<float> Vec4f;
typedef TVector4<double> Vec4d;

typedef TVector3<scalar_t> Vec3;
typedef TVector3<float> Vec3f;
typedef TVector3<double> Vec3d;

typedef TVector2<scalar_t> Vec2;
typedef TVector2<float> Vec2f;
typedef TVector2<double> Vec2d;
#endif

#endif
