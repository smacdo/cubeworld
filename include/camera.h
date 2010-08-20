#ifndef SCOTT_ROGEULIKE_CAMERA_H
#define SCOTT_ROGUELIKE_CAMERA_H

#include "math/vector.h"

class Camera
{
public:
    Camera();
    Camera( const Vec3& center );
    Camera( const Camera& camera );

    /**
     * Resets the camera to its starting position (usually world center)
     */
    void reset();

    /**
     * Moves the camera center to the specified location
     */
    void resetTo( const Vec3& center );

    /**
     * Resets the camera's looking_at vector. This will have the effect
     * of rotating the camera's view back to the default look_at, but the
     * camera's center will be unchanged.
     */
    void resetDirection();

    void moveForward()  { moveForward(  m_baseSpeed ); }
    void moveBackward() { moveBackward( m_baseSpeed ); }
    void strafeLeft()   { strafeLeft(   m_baseSpeed ); }
    void strafeRight()  { strafeRight(  m_baseSpeed ); }
    
    void moveForward(  float distance );
    void moveBackward( float distance );
    void strafeLeft(   float distance );
    void strafeRight(  float distance );

    void addMouseLookDelta( float deltaX, float deltaY );

    /**
     * Returns a position vector representing the camera's center
     */
    Vec3 center() const { return m_center; }

    /**
     * Returns a vector representing the direction that the camera is
     * facing  (eg, the "look" vector)
     *
     * TODO double check that this is returned as a unit vector
     */
    Vec3 direction() const { return m_direction; }

    /**
     * Returns a vector representing the direction of "up" for the
     * camera
     * 
     * TODO double check that this is a unit vector
     */
    Vec3 up() const { return m_up; }

    /**
     * Returns the viewing distance of the camera. That is, the distance
     * at which objects fade from view
     */
    float viewDistance() const { return m_viewDistance; }

    /**
     * Debugging method that will instruct the camera to print lots of
     * useful information to the debugging console
     */
    void printDebugInfo() const;

protected:
    void rotateYAxis( float angle );
    void rotateXAxis( float angle );

private:
    Vec3 m_center;
    Vec3 m_direction;
    Vec3 m_up;
    Vec3 m_right;
    Vec3 m_rotation;        // used for debugging purposes only
    

    float m_viewDistance;
    float m_baseSpeed;

};

#endif
