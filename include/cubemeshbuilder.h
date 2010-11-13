#ifndef SCOTT_ROGUELIKE_CUBEMESHBUILDER_H
#define SCOTT_ROGUELIKE_CUBEMESHBUILDER_H

#include <stdint.h>
#include <vector>

#include "math/vector.h"

struct GlVertex
{
    GlVertex( const Vec3& p, const Vec3& n, const Vec3& t )
    {
        pos[0]    = p[0]; pos[1]    = p[1]; pos[2]    = p[2];
        normal[0] = n[0]; normal[1] = n[1]; normal[2] = n[2];
        tex[0]    = t[0]; tex[1]    = t[1];
    }

    float pos[3];           // 4x3 --> 12 / 12
    float normal[3];        // 4x3 --> 12 / 24
    float tex[2];           // 4x2 -->  8 / 32
};

struct CubeChunkMesh
{
    CubeChunkMesh( unsigned int vbo_id, unsigned int ibo_id, size_t faceCount )
        : vbid( vbo_id ),
          ibid( ibo_id ),
          faceCount( faceCount )
    {
    }

    unsigned int vbid;
    unsigned int ibid;
    size_t faceCount;
};

class CubeMeshBuilder
{
public:
    CubeMeshBuilder();

    void addCube( const Vec3& );

    CubeChunkMesh createMesh();

    void addFace( const Vec3& pA, const Vec3& nA,
                  const Vec3& pB, const Vec3& nB,
                  const Vec3& pC, const Vec3& nC,
                  const Vec3& pD, const Vec3& nD );

    size_t numIndices() const;
    size_t numFaces()   const;
    size_t numVerts()   const;

private:
    std::vector<int>      faces;
    std::vector<GlVertex> vertices;
    int m_offset;
};

#endif
