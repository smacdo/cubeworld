#ifndef SCOTT_ROGUELIKE_GEOMETRY_H
#define SCOTT_ROGUELIKE_GEOMETRY_H

class Plane
{
public:
    float dist( const Vec3& point ) const;

    bool intersects( const Ray& ray ) const;
    bool intersects( const Ray& ray, float& distance ) const;

private:
    Vec3 m_center;
    float offset;
};

#endif
