#include "cubemeshbuilder.h"
#include "math/vector.h"

#include <stdint.h>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>


CubeMeshBuilder::CubeMeshBuilder()
    : m_offset(0)
{
    faces.reserve( 150000 );
    vertices.reserve( 35000 );
}

void CubeMeshBuilder::addCube( const Vec3& )
{

}

CubeChunkMesh CubeMeshBuilder::createMesh()
{
    //
    // Create a vertex and index buffer to store geometry
    //
    const int vertexElementSize = 3*4 + 3*4 + 2*4; // f3f3f2 --> 32 bytes
    const int indexElementSize  = 3*4;             // i3     --> 12 bytes

    int vbsize = vertexElementSize * vertices.size();
    int ibsize = indexElementSize  * faces.size();

    uint32_t vbid = 0, ibid = 0;

    // Get a buffer id
    glGenBuffers( 1, &vbid );
    glGenBuffers( 1, &ibid );

    assert( vbid > 0 );
    assert( ibid > 0 );

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
void CubeMeshBuilder::addFace( const Vec3& pA, const Vec3& nA,
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

size_t CubeMeshBuilder::numIndices() const { return faces.size(); }
size_t CubeMeshBuilder::numFaces()   const { return faces.size() / 3; }
size_t CubeMeshBuilder::numVerts()   const { return faces.size(); }