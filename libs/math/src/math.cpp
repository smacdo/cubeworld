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
#include "mathlib.h"

// matrix template instantiation
template class TMatrix4<float>;
template class TMatrix4<double>;
template class TMatrix4<int>;

template void swap( TMatrix<float,4>&  lhs, TMatrix<float,4>&  rhs );
template void swap( TMatrix<double,4>& lhs, TMatrix<double,4>& rhs );
template void swap( TMatrix<int,4>&    lhs, TMatrix<int,4>&    rhs );

//  Matrix 2x2
template class TMatrix2<float>;
template class TMatrix2<double>;
template class TMatrix2<int>;

template void swap( TMatrix<float,2>&  lhs, TMatrix<float,2>&  rhs );
template void swap( TMatrix<double,2>& lhs, TMatrix<double,2>& rhs );
template void swap( TMatrix<int,2>&    lhs, TMatrix<int,2>&    rhs );

// vector template instantiation
template class TVector3<float>;
template class TVector3<double>;
template class TVector3<int>;
template class TVector3<char>;

// vector function templatse
template Vec3  cross<float>( const Vec3&, const Vec3& );
template IVec3 cross<int>( const IVec3&, const IVec3& );

// mathlib math utilities
template float  min<float>(  const float&,  const float&  );
template double min<double>( const double&, const double& );
template long   min<long>(   const long&,   const long& );
template int    min<int>(    const int&,    const int& );
template short  min<short>(  const short&,  const short& );
template char   min<char>(   const char&,   const char& );

template float  max<float>(  const float&,  const float&  );
template double max<double>( const double&, const double& );
template long   max<long>(   const long&,   const long& );
template int    max<int>(    const int&,    const int& );
template short  max<short>(  const short&,  const short& );
template char   max<char>(   const char&, const char& );

template int    wrap<int>( const int&, const int& );

template float  lerp<float>( const float&, const float&, const float& );
template float  lerp<float>( const float&, const float&, const double& );
template float  lerp<float>( const float&, const float&, const int& );
template double lerp<double>( const double&, const double&, const double& );
template int    lerp<int>( const int&, const int&, const int& );
template Vec3   lerp<Vec3,float>( const Vec3&, const Vec3&, const float& );
template Vec3   lerp<Vec3,double>( const Vec3&, const Vec3&, const double& );
template Vec3   lerp<Vec3,int>( const Vec3&, const Vec3&, const int& );

template int    snap<int>( const int&, const int& );

template unsigned long  min<unsigned long>(  const unsigned long&,
                                             const unsigned long& );
template unsigned int   min<unsigned int>(   const unsigned int&, 
                                             const unsigned int& );
template unsigned short min<unsigned short>( const unsigned short&,
                                             const unsigned short& );
template unsigned char  min<unsigned char>(  const unsigned char&,
                                           const unsigned char& );
template unsigned long  max<unsigned long>(  const unsigned long&,
                                             const unsigned long& );
template unsigned int   max<unsigned int>(   const unsigned int&, 
                                             const unsigned int& );
template unsigned short max<unsigned short>( const unsigned short&,
                                             const unsigned short& );
template unsigned char  max<unsigned char>(  const unsigned char&,
                                           const unsigned char& );
