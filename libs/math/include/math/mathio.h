/**
 * Copyright 2010 Scott MacDonald. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *   1. Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Scott MacDonald ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Scott MacDonald OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of Scott MacDonald.
 */
#ifndef SCOTT_MATHLIB_IO_H
#define SCOTT_MATHLIB_IO_H

#include "math/matrix.h"
#include "math/vector.h"

// Nobody likes excessive #includes cluttering their headers, especially
// when core math classes are carrying around #include <iostream>
//
// This header contains prototypes for stream operations on all basic
// math types. Include this when you need this functionality
//   (eg, you are using cout)
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Standard iostream operators
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

template<typename T>
std::ostream& operator << ( std::ostream& os, const TVector3<T>& vec )
{
    os << "<" << vec.x() << ", " << vec.y() << ", " << vec.z() << ">";
    return os;
}


/////////////////////////////////////////////////////////////////////////////
// Compression methods
/////////////////////////////////////////////////////////////////////////////


#endif
