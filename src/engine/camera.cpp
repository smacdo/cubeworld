#include "camera.h"
#include "math/vector.h"
#include "math/matrix.h"

#include <cmath>
#include <iostream>

#define CAMERA_DEBUG 1
const Vec3 DefaultCameraCenter( 0.0f, 0.0f, 10.0f );

Camera::Camera()
    : mCenter( DefaultCameraCenter ),
      mDirection( 0.0f, 0.0f, -1.0f ),
      mUp( 0.0f, 1.0f, 0.0f ),
      mRight( 1.0f, 0.0f, 0.0f ),
      mRotation( 0.0f, 0.0f, 0.0f ),
      mViewDistance( 1000.0f ),
      mBaseSpeed( 0.25 )
{
}

Camera::Camera( const Vec3& center )
    : mCenter( center ),
      mDirection( 0.0f, 0.0f, -1.0f ),
      mUp( 0.0f, 1.0f, 0.0f ),
      mRight( 1.0f, 0.0f, 0.0f ),
      mRotation( 0.0f, 0.0f, 0.0f ),
      mViewDistance( 1000.0f ),
      mBaseSpeed( 0.25 )
{
}

Camera::Camera( const Camera& cam )
    : mCenter( cam.mCenter ),
      mDirection( cam.mDirection ),
      mUp( cam.mUp ),
      mRight( cam.mRight ),
      mRotation( cam.mRotation ),
      mViewDistance( cam.mViewDistance ),
      mBaseSpeed( cam.mBaseSpeed )
{
}

void Camera::reset()
{
    resetTo( Vec3( DefaultCameraCenter ) );
}

void Camera::resetTo( const Vec3& center )
{
    mCenter       = center;
    mDirection    = Vec3( 0.0f, 0.0f, -1.0f );
    mUp           = Vec3( 0.0f, 1.0f,  0.0f );
    mRight        = Vec3( 1.0f, 0.0f,  0.0f );
    mRotation     = Vec3( 0.0f, 0.0f,  0.0f );
    mViewDistance = 1000.0f;
}

void Camera::resetDirection()
{
    mDirection    = Vec3( 0.0f, 0.0f, -1.0f );
    mUp           = Vec3( 0.0f, 1.0f, 0.0f );
    mRight        = Vec3( 1.0f, 0.0f, 0.0f );
    mRotation     = Vec3( 0.0f, 0.0f, 0.0f );
}

void Camera::moveForward( float distance )
{
    mCenter += mDirection * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:FOWARD, center: " << mCenter << std::endl;
#endif
}

void Camera::moveBackward( float distance )
{
    mCenter -= mDirection * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:BACKWARD, center: " << mCenter << std::endl;
#endif
}

void Camera::strafeLeft( float distance )
{
    mCenter += cross( mDirection, mUp ) * -distance;
    mCenter += Vec3( -distance, 0.0, 0.0 );

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:SLEFT, center: " << mCenter << std::endl;
#endif
}

void Camera::strafeRight( float distance )
{
    mCenter += cross( mDirection, mUp ) * distance;

#ifdef CAMERA_DEBUG
    std::cout << "CAMERA:SRIGHT, center: " << mCenter << std::endl;
#endif
}

float deg2rad( float d )
{
    return d / 180.0f / 3.141592654f;
}

void Camera::rotateYAxis( float angle )
{
    mRotation[1] += angle;
    float r = deg2rad( angle );

    // Rotate direction around the up vector
    Vec3 result = (mDirection * cos(r)) - (mRight * sin(r));
    mDirection = normalized( result );

    // Recompute right vector by using cross product
    result = cross( mDirection, mUp );
    mRight = normalized( result );
}

void Camera::rotateXAxis( float angle )
{
    mRotation[0] += angle;     // debugging info, sum of rotation
    float r = deg2rad( angle );

    // Rotate direction around the right vector
    Vec3 result = (mDirection * cos(r)) + (mUp * sin(r));
    mDirection = normalized( result );

    // Recompute up vector using cross product
    result      = cross( mDirection, mRight ) * -1;
    mRight     = normalized( result );
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
                  << mCenter[0] << ", "
                  << mCenter[1] << ", "
                  << mCenter[2] << std::endl
              << "\tDIRECTION: "
                  << mDirection[0] << ", "
                  << mDirection[1] << ", "
                  << mDirection[2] << std::endl
              << "\tUP: "
                  << mUp[0] << ", "
                  << mUp[1] << ", "
                  << mUp[2] << std::endl
              << "\tRIGHT: "
                  << mRight[0] << ", "
                  << mRight[1] << ", "
                  << mRight[2] << ", " << std::endl
              << "\tROTATION: "
                  << mRotation[0] << ", "
                  << mRotation[1] << ", "
                  << mRotation[2] << ", " << std::endl
              << "\tVIEWDIST : "
                  << mViewDistance << std::endl;
}

