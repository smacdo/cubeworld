#include "camera.h"
#include "math/vector.h"
#include "math/matrix.h"

#include <cmath>
#include <iostream>

#define CAMERA_DEBUG 1

Camera::Camera()
    : m_center( 0, 0, 10 ),
      m_direction( 0, 0, -1 ),
      m_up( 0, 1, 0 ),
      m_viewDistance( 1000.0f ),
      m_baseSpeed( 0.25 )
{
}

Camera::Camera( const Vec3& center )
    : m_center( center ),
      m_direction( 0, 0, -1 ),
      m_up( 0, 1, 0 ),
      m_viewDistance( 1000.0f ),
      m_baseSpeed( 0.25 )
{
}

Camera::Camera( const Camera& cam )
    : m_center( cam.m_center ),
      m_direction( cam.m_direction ),
      m_up( cam.m_up ),
      m_viewDistance( cam.m_viewDistance ),
      m_baseSpeed( cam.m_baseSpeed )
{
}

void Camera::reset()
{
    resetTo( Vec3( 0.0, 0.0, -0.25 ) );
}

void Camera::resetTo( const Vec3& center )
{
    m_center       = center;
    m_direction    = Vec3( 0, 0, -1 );
    m_up           = Vec3( 0, 1,  0 );
    m_viewDistance = 1000.0f;
}

void Camera::resetDirection()
{
    m_direction    = Vec3( 0, 0, -1 );
}

void Camera::moveForward( float distance )
{
    m_center += m_direction * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:FOWARD, center: "
              << m_center[0] << ", "
              << m_center[1] << ", "
              << m_center[2]
              << std::endl;
#endif
}

void Camera::moveBackward( float distance )
{
    m_center -= m_direction * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:BACKWARD, center: "
              << m_center[0] << ", "
              << m_center[1] << ", "
              << m_center[2]
              << std::endl;
#endif
}

void Camera::strafeLeft( float distance )
{
    m_center += cross( m_direction, m_up ) * -distance;
    m_center += Vec3( -distance, 0.0, 0.0 );

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:SLEFT, center: "
              << m_center[0] << ", "
              << m_center[1] << ", "
              << m_center[2]
              << std::endl;
#endif
}

void Camera::strafeRight( float distance )
{
    m_center += cross( m_direction, m_up ) * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:SRIGHT, center: "
              << m_center[0] << ", "
              << m_center[1] << ", "
              << m_center[2]
              << std::endl;
#endif
}

float deg2rad( float d )
{
    return d / 180.0f / 3.141592654f;
}

Vec3 rotateYAxis( const Vec3& v, float angle )
{
    float r = deg2rad( angle );

    float x = v[2] * sin(r) + v[0] * cos(r);
    float y = v[1];
    float z = v[2] * cos(r) - v[0] * sin(r);

    return Vec3( x, y, z );
}

Vec3 rotateXAxis( const Vec3& v, float angle )
{
    float r = deg2rad( angle );

    float x = v[0];
    float y = v[1] * cos(r) - v[2] * sin(r);
    float z = v[1] * sin(r) + v[2] * cos(r);

    return Vec3( x, y, z );
}

void Camera::addMouseLookDelta( float deltaX, float deltaY )
{
    if ( deltaY != 0.0f )
    {
        Vec3 result = rotateYAxis( m_direction, deltaY );
        m_direction = result.normalized();
    }

    if ( deltaX != 0.0f )
    {
        Vec3 result = rotateXAxis( m_direction, deltaX );
        m_direction = result.normalized();
    }

#ifdef CAMERA_DEBUG
  /*      std::cout << "CAMERA:ROTATE " << std::endl
                  << "\tdX="   << deltaX << ", dY=" << deltaY << std::endl
                  << "\trY_X=" << x << "rY_Y=" << y << std::endl
                  << "\tdir="  << m_direction[0] << ", "
                               << m_direction[1] << ", "
                               << m_direction[2]
                  << std::endl;*/
#endif
}

void Camera::printDebugInfo() const
{
    std::cout << "CAMERA INFORMATION" << std::endl
              << "\tCENTER   : "
                  << m_center[0] << ", "
                  << m_center[1] << ", "
                  << m_center[2] << std::endl
              << "\tDIRECTION: "
                  << m_direction[0] << ", "
                  << m_direction[1] << ", "
                  << m_direction[2] << std::endl
              << "\tUP: "
                  << m_up[0] << ", "
                  << m_up[1] << ", "
                  << m_up[2] << std::endl
              << "\tVIEWDIST : "
                  << m_viewDistance << std::endl;
}

