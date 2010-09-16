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

template float  dot<float>( const Vec3&, const Vec3& );
template int    dot<int>( const IVec3&, const IVec3& );

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
