#ifndef SANDBOX_MATH_IO_H
#define SANDBOX_MATH_IO_H

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
