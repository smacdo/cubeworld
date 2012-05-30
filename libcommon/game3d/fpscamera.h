#ifndef SCOTT_COMMON_GEOM_FPSCAMERA_H
#define SCOTT_COMMON_GEOM_FPSCAMERA_H

#include <geom/camera.h>

#include <math/vector.h>
#include <math/matrix.h>

class FpsCamera : public Camera
{
public:
    FpsCamera( const Vec3& center );

    void moveForward()  { moveForward(  m_baseSpeed ); }
    void moveBackward() { moveBackward( m_baseSpeed ); }
    void strafeLeft()   { strafeLeft(   m_baseSpeed ); }
    void strafeRight()  { strafeRight(  m_baseSpeed ); }
    
    void moveForward(  float distance );
    void moveBackward( float distance );
    void strafeLeft(   float distance );
    void strafeRight(  float distance );

    void addMouseLookDelta( float deltaX, float deltaY );

    virtual void printDebugInfo() const;

protected:
    void rotateYAxis( float angle );
    void rotateXAxis( float angle );

private:
    float m_baseSpeed;

};

#endif
