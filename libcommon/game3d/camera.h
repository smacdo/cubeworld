#ifndef SCOTT_COMMON_GEOM_CAMERA_H
#define SCOTT_COMMON_GEOM_CAMERA_H

#include <math/vector.h>
#include <math/matrix.h>

class Camera
{
public:
    Camera();
    Camera( const Vec3& center );
    Camera( const Camera& camera );

    virtual ~Camera();

    /**
     * Resets the camera to its starting position (usually world center)
     */
    virtual void reset();

    /**
     * Moves the camera center to the specified location
     */
    virtual void resetTo( const Vec3& center );

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
    virtual void printDebugInfo() const;

    virtual Mat4 createProjectionMatrix() const;

private:
    Vec3 m_center;
    Vec3 m_direction;
    Vec3 m_up;
    Vec3 m_right;
    Vec3 m_rotation;

    float m_viewDistance;
};

#endif
