#include "camera.h"
#include "math/vector.h"
#include "math/matrix.h"

#include <cmath>
#include <iostream>

#define CAMERA_DEBUG 1
const Vec3 DefaultCameraCenter( 0.0f, 0.0f, 10.0f );

Camera::Camera()
    : m_center( DefaultCameraCenter ),
      m_direction( 0.0f, 0.0f, -1.0f ),
      m_up( 0.0f, 1.0f, 0.0f ),
      m_right( 1.0f, 0.0f, 0.0f ),
      m_rotation( 0.0f, 0.0f, 0.0f ),
      m_viewDistance( 1000.0f ),
      m_baseSpeed( 0.25 )
{
}

Camera::Camera( const Vec3& center )
    : m_center( center ),
      m_direction( 0.0f, 0.0f, -1.0f ),
      m_up( 0.0f, 1.0f, 0.0f ),
      m_right( 1.0f, 0.0f, 0.0f ),
      m_rotation( 0.0f, 0.0f, 0.0f ),
      m_viewDistance( 1000.0f ),
      m_baseSpeed( 0.25 )
{
}

Camera::Camera( const Camera& cam )
    : m_center( cam.m_center ),
      m_direction( cam.m_direction ),
      m_up( cam.m_up ),
      m_right( cam.m_right ),
      m_rotation( cam.m_rotation ),
      m_viewDistance( cam.m_viewDistance ),
      m_baseSpeed( cam.m_baseSpeed )
{
}

void Camera::reset()
{
    resetTo( Vec3( DefaultCameraCenter ) );
}

void Camera::resetTo( const Vec3& center )
{
    m_center       = center;
    m_direction    = Vec3( 0.0f, 0.0f, -1.0f );
    m_up           = Vec3( 0.0f, 1.0f,  0.0f );
    m_right        = Vec3( 1.0f, 0.0f,  0.0f );
    m_rotation     = Vec3( 0.0f, 0.0f,  0.0f );
    m_viewDistance = 1000.0f;
}

void Camera::resetDirection()
{
    m_direction    = Vec3( 0.0f, 0.0f, -1.0f );
    m_up           = Vec3( 0.0f, 1.0f, 0.0f );
    m_right        = Vec3( 1.0f, 0.0f, 0.0f );
    m_rotation     = Vec3( 0.0f, 0.0f, 0.0f );
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

void Camera::rotateYAxis( float angle )
{
    m_rotation[1] += angle;     // debugging info, sum of rotation
    float r = deg2rad( angle );

    // Rotate direction around the up vector
    Vec3 result = (m_direction * cos(r)) - (m_right * sin(r));
    m_direction = result.normalized();

    // Recompute right vector by using cross product
    result      = cross( m_direction, m_up );
    m_right     = result.normalized();
}

void Camera::rotateXAxis( float angle )
{
    m_rotation[0] += angle;     // debugging info, sum of rotation
    float r = deg2rad( angle );

    // Rotate direction around the right vector
    Vec3 result = (m_direction * cos(r)) + (m_up * sin(r));
    m_direction = result.normalized();

    // Recompute up vector using cross product
    result      = cross( m_direction, m_right ) * -1;
    m_right     = result.normalized();
}

void Camera::addMouseLookDelta( float deltaX, float deltaY )
{
    if ( deltaY != 0.0f )
    {
        rotateYAxis( deltaY );
    }

    if ( deltaX != 0.0f )
    {
        rotateXAxis( deltaX );
    }
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
              << "\tRIGHT: "
                  << m_right[0] << ", "
                  << m_right[1] << ", "
                  << m_right[2] << ", " << std::endl
              << "\tROTATION: "
                  << m_rotation[0] << ", "
                  << m_rotation[1] << ", "
                  << m_rotation[2] << ", " << std::endl
              << "\tVIEWDIST : "
                  << m_viewDistance << std::endl;
}

