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
#ifndef SCOTT_MATH_MATRIX_UTILS_H
#define SCOTT_MATH_MATRIX_UTILS_H

#include <math/matrix.h>
#include <math/vector.h>

namespace MatrixUtil
{
    /**
     * Generates a new matrix that rotates around the X axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundX( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, c,    -s,   0.0f,
                            0.0f, s,     c,   0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates around the Y axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundY( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( c,    0.0f, -s,   0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            s,    0.0f, c,    0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates around the Z axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundZ( T angle )
    {
        T s = sinf( angle );
        T c = cosf( angle );

        return TMatrix4<T>( c,    -s,   0.0f, 0.0f,
                            s,    c,    0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Generates a new matrix that rotates any given vector around the
     * specified axis
     */
    template<typename T>
    TMatrix4<T> createRotationAroundAxis( T /*xAngle*/,
                                          T /*yAngle*/,
                                          T /*zAngle*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates a translation matrix
     */
    template<typename T>
    TMatrix4<T> createTranslation( T x, T y, T z )
    {
        return TMatrix4<T>( 1.0f, 0.0f, 0.0f, x,
                            0.0f, 1.0f, 0.0f, y,
                            0.0f, 0.0f, 1.0f, z,
                            0.0f, 0.0f, 0.0f, 1.0f );
    }

    /**
     * Creates a uniform scaling matrix
     */
    template<typename T>
    TMatrix4<T> createScale( T k )
    {
        return TMatrix4<T>( k,    0.0f, 0.0f, 0.0f,
                            0.0f, k,    0.0f, 0.0f,
                            0.0f, 0.0f, k,    0.0f,
                            1.0f, 1.0f, 1.0f, 1.0f );
    }

    /**
     * Creates a view matrix that looks from a specified eye position to
     * the center position and with the given up vector.
     *
     * Similiar to gluLookAt
     */
    template<typename T>
    TMatrix4<T> createLookAt( const TVector3<T>& /*eye*/,
                              const TVector3<T>& /*lookAt*/,
                              const TVector3<T>& /*up*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates an OpenGL compatible perspective projection
     */
    template<typename T>
    TMatrix4<T> createFrustum( T /*left*/,
                               T /*right*/,
                               T /*bottom*/,
                               T /*top*/,
                               T /*zNear*/,
                               T /*zFar*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates an OpenGL compatible orthographic projection matrix
     */
    template<typename T>
    TMatrix4<T> createOrtho( T /*left*/,
                             T /*right*/,
                             T /*bottom*/,
                             T /*top*/,
                             T /*zNear*/,
                             T /*zFar*/ )
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates a matrix using parameters specified in row order form
     */
    template<typename T>
    TMatrix4<T> createRowOrder()
    {
        return TMatrix4<T>::IDENTITY;
    }

    /**
     * Creates a matrix using parameters specified in column order form
     */
    template<typename T>
    TMatrix4<T> createColOrder()
    {
        return TMatrix4<T>::IDENTITY;
    }
};

#endif
