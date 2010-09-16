#ifndef SCOTT_ROGUELIKE_CUBEMESHBUILDER_H
#define SCOTT_ROGUELIKE_CUBEMESHBUILDER_H

#include <stdint.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

struct GlVertex
{
    GlVertex( const Vec3& p, const Vec3& n, const Vec3& t )
    {
        pos[0]    = p[0]; pos[1]    = p[1]; pos[2]    = p[2];
        normal[0] = n[0]; normal[1] = n[1]; normal[2] = n[2];
        tex[0]    = t[0]; tex[1]    = t[1]; tex[2]    = t[2];
    }

    float pos[3];           // 4x3 --> 12 / 12
    float normal[3];        // 4x3 --> 12 / 24
    float tex[2];           // 4x2 -->  8 / 32
};

struct CubeChunkMesh
{
    CubeChunkMesh( GLuint vbo_id, GLuint ibo_id, int faceCount )
        : vbid( vbo_id ),
          ibid( ibo_id ),
          faceCount( faceCount )
    {
    }

    GLuint vbid;
    GLuint ibid;
    int faceCount;
};

class CubeMeshBuilder
{
public:
    CubeMeshBuilder()
        : m_offset(0)
    {
        faces.reserve( 150000 );
        vertices.reserve( 35000 );
    }

    void addCube( const Vec3& position )
    {

    }

    CubeChunkMesh createMesh()
    {
        //
        // Create a vertex and index buffer to store geometry
        //
        const int vertexElementSize = 3*4 + 3*4 + 2*4; // f3f3f2 --> 32 bytes
        const int indexElementSize  = 3*4;             // i3     --> 12 bytes

        int vbsize = vertexElementSize * vertices.size();
        int ibsize = indexElementSize  * faces.size();

        uint32_t vbid = -1, ibid = -1;

        // Get a buffer id
        glGenBuffers( 1, &vbid );
        glGenBuffers( 1, &ibid );

        assert( vbid != -1 );
        assert( ibid != -1 );

        // Set the buffer to be active, and copy the vertex buffer data in
        glBindBuffer( GL_ARRAY_BUFFER, vbid );
        glBufferData( GL_ARRAY_BUFFER, vbsize, &vertices[0], GL_STATIC_DRAW );

        // Set the index buffer to be active
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibid );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibsize, &faces[0], GL_STATIC_DRAW );

        return CubeChunkMesh( vbid, ibid, faces.size() );
    }

    /**
     * A - D
     * | / |
     * B - C
     *
     * [BDA]
     * [BDC]
     */
    void addFace( const Vec3& pA, const Vec3& nA,
                  const Vec3& pB, const Vec3& nB,
                  const Vec3& pC, const Vec3& nC,
                  const Vec3& pD, const Vec3& nD )
    {
        vertices.push_back(GlVertex( pA, nA, Vec3( 0.0, 0.0, 0.0 ) ));
        vertices.push_back(GlVertex( pB, nB, Vec3( 0.0, 1.0, 0.0 ) ));
        vertices.push_back(GlVertex( pC, nC, Vec3( 1.0, 1.0, 0.0 ) ));
        vertices.push_back(GlVertex( pD, nD, Vec3( 1.0, 0.0, 0.0 ) ));

        // [BDA] --> [130]
        faces.push_back( m_offset + 1 );
        faces.push_back( m_offset + 3 );
        faces.push_back( m_offset + 0 );

        // [CDB] --> [231]
        faces.push_back( m_offset + 2 );
        faces.push_back( m_offset + 3 );
        faces.push_back( m_offset + 1 );

        m_offset += 4;
    }

    size_t numIndices() const { return faces.size(); }
    size_t numFaces()   const { return faces.size() / 3; }
    size_t numVerts()   const { return faces.size(); }

private:
    std::vector<int>      faces;
    std::vector<GlVertex> vertices;
    int m_offset;
};

#endif
