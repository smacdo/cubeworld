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
#ifndef SCOTT_MATHLIB_MATRIX_H
#define SCOTT_MATHLIB_MATRIX_H

#include <algorithm>
#include <functional>
#include <math/config.h>
#include <math/util.h>

#if MATH_DEBUG_MODE == 1
#   include <limits>
#   define MATRIX_DEBUG_MODE 1
#   define matrix_assert(x) assert(x)
#   define INIT_MATRIX_TO_ZERO 1
#else
#   define matrix_assert(x)
#endif

/**
 * A templated, size-indepdent column major matrix. This templated matrix can
 * accomodate any N-sized square matrix that is sized NxN. The matrix stores
 * its values in column major format (each column is stored contigously),
 * rather than in row major format (where each row is stored contigously). This
 * is done because OpenGL uses column major format, and converting between the
 * two formats continously would be confusing.
 *
 * If you are using common matrix sizes (2x2, 3x3, 4x4), do not instantiate
 * this class directly. All of the common matrix sizes have their own classes
 * that inherit from this class and provide additional helper constructors. For
 * example, if you wish to construct a 4x4 float matrix,
 *
 *     DO  : TMatrix4<float>
 *     DONT: TMatrix<float,4>
 *
 * Additionally, while the matrices store their values internally in a column
 * major format, the constructors expect their values to be provided in row
 * major format. This might seem awkward and confusing, until you realize that
 * this allows you to call constructors with the "standard" matrix notation.
 *
 * Pretend you have a 3x3 matrix as follows
 *    
 *    M = [ A B C
 *          D E F
 *          G H I ]
 *
 * When calling Matrix3's constructor, you would call it like:
 *
 *    DO  : TMatrix3<float>( A, B, C,
 *                           D, E, F,
 *                           G, H, I )
 *
 * Even though the matrix stores the values like: [ A D G B E H C F I ]. The
 * only time you need concern yourself with this storage information is when:
 *    A) You call a TMatrix<T,N>( T* ) constructor that takes a pointer to a
 *       1d array
 *    B) You call TMatrix<T,N>::ptr() that returns a pointer to a 1d array
 *
 *
 *
 * That should be enough documentation to cover the matrix class. Otherwise the
 * matrix class (and derived classes) should behave as you expect. They
 * overload all the proper mathmatical operators, and implement the expected
 * helper methods. See method documentation for more information on individual
 * methods, or see the unit tests for examples on how they are used.
 */
template<typename T, int N>
class TMatrix
{
    public:
        /**
         * Default fast constructor - When created, the matrix 
         * is initially uninitialized.
         */
        TMatrix()
        {
#ifdef INIT_MATRIX_TO_ZERO
            std::fill( m, m + N*N, T() );
#endif
        }

        /**
         * Construct a matrix from an array of values. The 
         * constructor assumes the values are listed in column-major
         * rather than row-major format.
         *
         * IMPORTANT NOTE: This constructor expects the array in
         * column-major format!!! Not row major like the value constructors
         *
         * eg [ m11 m21 m23 m21 m22 ... ] rather than [ m11 m21 ... ]
         */
        explicit TMatrix( const T * vals )
        {
            matrix_assert( NULL != vals );
            std::copy( vals, vals + N*N, m );
        }

        /**
         * Copy constructor for matrix. Initialize this matrix to the 
         * value of the provided matrix.
         */
        TMatrix( const TMatrix<T,N>& mat )
        {
            std::copy( mat.m, mat.m + (N*N), m );
        }

        /**
         * Constant pointer to matrix structure. Lets the user cast this
         * class to const T*
         */
        const T* ptr() const
        {
            return m;
        }

        /**
         * Pointer to matrix's underlying data store. Lets the user cast
         * this class to T*
         */
        T* ptr()
        {
            return m;
        }

        /**
         * Index operator - Allows user to access the matrix's underlying
         * data array. Note that the matrix stores its value in column
         * major order
         */
        const T& operator[] ( int offset ) const
        {
            matrix_assert( offset < N*N && "Index on matrix out of range" );
            return m[offset];
        }

        T& operator[] ( int offset )
        {
            matrix_assert( offset < N*N && "Index on matrix out of range" );
            return m[offset];
        }

        /**
         * Assignment operator. Makes this matrix equal the value of the
         * given matrix on the right hand side.
         */
        const TMatrix<T,N>& operator = ( const TMatrix<T,N>& rhs )
        {
            std::copy( rhs.m, rhs.m + N*N, m );
            return *this;
        }

        /**
         * Addition operator - adds this matrix and another matrix together,
         * and returns the result of this operation as a new matrix.
         */
        const TMatrix<T,N> operator + ( const TMatrix<T,N>& rhs ) const
        {
            TMatrix<T,N> r( *this );

            std::transform( m, m + N*N, r.m,
                            r.m,
                            std::plus<T>()
            );

            return r;
        }

        /**
         * Self addition operator - adds the matrix on the right hand
         * side to this matrix.
         */
        void operator += ( const TMatrix<T,N>& rhs )
        {
            std::transform( m, m + N*N, rhs.m,
                            m,
                            std::plus<T>()
            );
        }

        /**
         * Subtraction operator - subtract the matrix on the right hand
         * side from this matrix, and return the result of this operation
         * as a new matrix.
         */
        const TMatrix<T,N> operator - ( const TMatrix<T,N>& rhs ) const
        {
            TMatrix<T,N> r( *this );

            std::transform( m, m + N*N, r.m,
                            r.m,
                            std::minus<T>()
            );

            return r;
        }

        /**
         * Self subtraction operator - subtract the provided right hand
         * matrix from ourself.
         */
        const TMatrix<T,N> operator -= ( const TMatrix<T,N>& rhs )
        {
            std::transform( m, m + N*N, rhs.m,
                            m,
                            std::plus<T>()
            );
        }

        /**
         * Matrix scaling operator
         */
        const TMatrix<T,N> operator * ( const T& c ) const
        {
            TMatrix<T,N> r( *this );

            std::transform( m, m + N*N,
                            r.m,
                            std::bind2nd( std::multiplies<T>(), c )
            );

            return r;
        }

        /**
         * Matrix self-scaling operator
         */
        const TMatrix<T,N> operator *= ( const T& c ) const
        {
            std::transform( m, m + N*N,
                            m,
                            std::bind2nd( std::multiplies<T>(), c )
            );
        }

        /**
         * Matrix multiplication
         */
        const TMatrix<T,N> operator * ( const TMatrix<T,N>& rhs ) const
        {
            // not implemented yet
            return TMatrix<T,N>();
        }

        /**
         * The equality operator will check if two matrices have equal
         * values. Depending on compile time constants, this method will
         * either use a strict equality check, or a slightly more relaxed
         * fuzzy equals. (Fuzzy equals is the default).
         */
        bool operator == ( const TMatrix<T,N>& rhs ) const
        {
#ifdef MATH_USE_FUZZY_EQUALS
            return std::equal( m, m + N*N, rhs.m, Math::equalsClose<T> );
#else
            return std::equal( m, m + N*N, rhs.m );
#endif
        }

       /**
        * The inequality operator. Simply checks if two matrices
        * are not equivilant.
        */
        bool operator != ( const TMatrix<T,N>& rhs ) const
        {
            return !( *this == rhs );
        }

        /**
         * Strict equality operator. This method will check if the values
         * of two matrices matches exactly.
         */
        bool equalsEact( const TMatrix<T,N>& rhs ) const
        {
            return std::equal( m, m + N*N, rhs.m );
        }

        /**
         * Fuzzy equals equality operator. This version of the equality
         * method checks to see if two matrices are identical, to a
         * relatively high precision ( +/- 0.00001 ).
         *
         * You normally want to use a fuzzy equals due to the nature
         * imprecise nature of floating point math. Overtime two identical
         * values will be begin to diverge as differing operations are
         * applied and imprecision issues come into play.
         */
        bool equalsClose( const TMatrix<T,N>& rhs ) const
        {
            return std::equal( m, m + N*N, rhs.m, Math::equalsClose<T> );
        }

        /**
         * Returns the value at the given (r,c) matrix cell.
         *
         * \param r The row of the matrix
         * \param c The column of the matrix
         * \return  The value of the matrix cell
         */
        T at( int r, int c ) const
        {
            matrix_assert( r >= 0 && r < N && "Row must be valid offset");
            matrix_assert( c >= 0 && c < N && "Col must be valid offset");

            return m[index(r,c)];
        }

        /**
         * Checks if the matrix is zeroed (eg, all the matrix cells
         * are equal to zero).
         */
        bool isZeroMatrix() const
        {
            bool status = true;

            for ( int i = 0; i < N*N; ++i )
            {
                if (! Math::isZero<T>( m[i] ) )
                {
                    status = false;
                    break;
                }
            }

            return status;
        }

        /**
         * Checks if the matrix is an identity matrix (1s down the
         * diagonal)
         */
        bool isIdentityMatrix() const
        {
            bool status = true;

            for ( int i = 0; i < N; ++i )
            {
                if (! Math::equalsClose( m[index(i,i)], static_cast<T>(1.0) ) )
                {
                    status = false;
                    break;
                }
            }

            return status;
        }

        /**
         * Returns the transpose of this matrix
         */
        TMatrix<T,N>& transpose() const
        {
            TMatrix<T,N> ret;
    
            // not implemented yet
            return ret;
        }

        /**
         * Swaps this matrix with another matrix of the same size of type
         */
        template<typename U, int V>
        friend void swap( TMatrix<U,V>& lhs, TMatrix<U,V>& rhs );

    protected:
        /**
         * Given a row and column index, returns an offset into the
         * matrix's array.
         *
         * (This assumes the matrix stores its value in column major order)
         */
        int index( int r, int c ) const
        {
            matrix_assert( r >= 0 && r < N && "Row must be valid offset");
            matrix_assert( c >= 0 && c < N && "Col must be valid offset");

            return c * N + r;
        }

        template<typename U, int V>
        friend std::ostream& operator << ( std::ostream& os,
                                           const TMatrix<U,V>& mat );

    protected:
        /**
         * The matrix cells
         */
        T m[N*N];
};

/////////////////////////////////////////////////////////////////////////////
// TMatrix<T,N> operators
/////////////////////////////////////////////////////////////////////////////
template<typename T, int N>
std::ostream& operator << ( std::ostream& os, const TMatrix<T,N>& mat )
{
    os << "[ ";

    for ( int r = 0; r < N; ++r )
    {
        os << "[";

        for ( int c = 0; c < N; ++c )
        {
            if ( c == N-1 )
            {
                os << mat.at( r, c );
            }
            else
            {
                os << mat.at( r, c ) << ", ";
            }
        }

        os << "]";

        if ( r == N-1 )
        {
            os << " ";
        }
        else
        {
            os << "; ";
        }
    }

    os << " ]";

    return os;
}


/////////////////////////////////////////////////////////////////////////////
// TMatrix<T,N> utility / friend methods
/////////////////////////////////////////////////////////////////////////////
template<typename T, int N>
void swap( TMatrix<T,N>& lhs, TMatrix<T,N>& rhs )
{
    T t;

    for ( int i = 0; i < N*N; ++i )
    {
        t        = lhs.m[i];
        lhs.m[i] = rhs.m[i];
        rhs.m[i] = t;
    }
}

/////////////////////////////////////////////////////////////////////////////
// A 4x4 column major format that inherits from TMatrix<T,N> and adds
// additional useful constructors / helper methods.
/////////////////////////////////////////////////////////////////////////////
template<typename T>
class TMatrix4 : public TMatrix<T,4>
{
    using TMatrix<T,4>::m;

public:
    /**
     * Empty matrix constructor - Creates a new, uninitialized
     * 4x4 matrix
     */
    TMatrix4()
        : TMatrix<T,4>()
    {
    }

    /**
     * 4x4 matrix constructor. Arguments to the constructor are
     * in the normal "expected" (row major) format, even though the
     * underlying matrix class will store these values in column major
     * format.
     *
     * eg, to construct [ [a, b, c, d]
     *                    [e, f, g, h]
     *                    [i, j, k, l]
     *                    [m, n, o, p] ]
     *
     * just call TMatrix4( a, b, c, d,
     *                     e, f, g, h,
     *                     i, j, k, l,
     *                     m, n, o, p );
     *
     * and the matrix will store these values in memory as follows:
     *  [ a, e, i, m, b, f, j, n, c, g, k, o, d, h, l, p ]
     * 
     */
    TMatrix4( const T& m11, const T& m12, const T& m13, const T& m14,
              const T& m21, const T& m22, const T& m23, const T& m24,
              const T& m31, const T& m32, const T& m33, const T& m34,
              const T& m41, const T& m42, const T& m43, const T& m44 )
    {
        m[0]  = m11; m[1]  = m21; m[2]  = m31; m[3]  = m41;
        m[4]  = m12; m[5]  = m22; m[6]  = m32; m[7]  = m42;
        m[8]  = m13; m[9]  = m23; m[10] = m33; m[11] = m43;
        m[12] = m14; m[13] = m24; m[14] = m34; m[15] = m44;
    }

    /**
     * Construct the 4x4 matrix with values from the provided pointer. The
     * provided array must be in column major format, and must contain at
     * least 16 values
     */
    TMatrix4( const T* vals )
        : TMatrix<T,4>( vals )
    {
    }

    /**
     * Copy constructor
     */
    TMatrix4( const TMatrix<T,4>& mat )
        : TMatrix<T,4>( mat )
    {
    }

    /**
     * Creates and returns a 4x4 identity matrix
     */
    static TMatrix4 IdentityMatrix()
    {
        return TMatrix4( 1.0, 0.0, 0.0, 0.0,
                         0.0, 1.0, 0.0, 0.0,
                         0.0, 0.0, 1.0, 0.0,
                         0.0, 0.0, 0.0, 1.0 );
    }

    /**
     * Creates and returns a 4x4 zero matrix
     */
    static TMatrix4 ZeroMatrix()
    {
        return TMatrix4( 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0 );
    }

    /**
     * Creates and returns a homogeneous 4x4 translation matrix
     */
    static TMatrix4 makeTranslationMatrix( const T& x,
                                           const T& y,
                                           const T& z )
    {
        return TMatrix4( 1.0, 0.0, 0.0, x,
                         0.0, 1.0, 0.0, y,
                         0.0, 0.0, 1.0, z,
                         0.0, 0.0, 0.0, 1.0 );
    }

    /**
     * Creates and returns a homogeneous 4x4 scaling matrix
     */
    static TMatrix4 makeScalingMatrix( const T& x,
                                       const T& y,
                                       const T& z )
    {
        return TMatrix4(   x, 0.0, 0.0, 0.0,
                         0.0,   y, 0.0, 0.0,
                         0.0, 0.0,   z, 0.0,
                         0.0, 0.0, 0.0, 1.0 );
    }

    /**
     * Creates and returns a homogenous 4x4 x-axis rotation matrix
     */
    static TMatrix4 makeXRotationMatrix( const T& a )
    {
        return TMatrix4( 1.0,     0.0,    0.0, 0.0,
                         0.0,  cos(a), sin(a), 0.0,
                         0.0, -sin(a), cos(a), 0.0,
                         0.0,     0.0,    0.0, 1.0 );
    }

    /**
     * Creates and returns a homogenous 4x4 y-axis rotation matrix
     */
    static TMatrix4 makeYRotationMatrix( const T& a )
    {
        return TMatrix4( cos(a), 0.0, -sin(a), 0.0,
                         0.0,    1.0,  0.0,    0.0,
                         sin(a), 0.0,  cos(a), 0.0,
                         0.0,    0.0,  0.0,    1.0 );
    }

    /**
     * Creates and returns a homogenous 4x4 z-axis rotation matrix
     */
    static TMatrix4 makeZRotationMatrix( const T& a )
    {
        return TMatrix4(  cos(a), sin(a), 0.0, 0.0,
                         -sin(a), cos(a), 0.0, 0.0,
                          0.0,    0.0,    1.0, 0.0,
                          0.0,    0.0,    0.0, 1.0 );
    }
};

/////////////////////////////////////////////////////////////////////////////
// A templated 2x2 matrix class that derives from TMatrixT,N> and implements
// useful constructors
/////////////////////////////////////////////////////////////////////////////
template<typename T>
class TMatrix2 : public TMatrix<T,2>
{
    using TMatrix<T,2>::m;      // yay bizzare lookup rules

public:
    /**
     * Empty constructor - creates a uninitialized 2x2 matrix
     */
    TMatrix2()
        : TMatrix<T,2>()
    {
    }

    /**
     * Creates a 2x2 matrix specified by provided arguments
     */
    TMatrix2( const T& m11, const T& m12,
              const T& m21, const T& m22 )
    {
        m[0] = m11; m[1] = m21;
        m[2] = m12; m[3] = m22;
    }

    TMatrix2( const T* vals )
        : TMatrix<T,2>(vals)
    {
    }

    TMatrix2( const TMatrix<T,2>& mat )
        : TMatrix<T,2>(mat)
    {
    }
};

#endif
