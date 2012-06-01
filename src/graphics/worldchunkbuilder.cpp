#include "graphics/worldchunkbuilder.h"
#include "math/vector.h"

#include <stdint.h>
#include <vector>

WorldChunkBuilder::WorldChunkBuilder()
    : m_offset(0)
{
    faces.reserve( 150000 );
    vertices.reserve( 35000 );
}


// TODO remove this from worldchunk, use a visitAllCubes()
// visitor pattern to build the mesh
/*
WorldChunkMesh WorldChunkBuilder::createMesh() const
{
    
    //
    // Cube positions
    //   TODO: rearrange these to fit correct builder pattern
    //      (ABCD, not ADCB)
    // [AB        
    //  DC]    -->  ADCB    
    //
    //   xyz
    //   1. right
    //   2. left
    //   3. back
    //   4. front
    //   5. top
    //   6. bottom
    Vec3 CubePos[6][4] = 
    {
        {   // right
            Vec3( 1.0f, 1.0f, 0.0f ),
            Vec3( 1.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 1.0f,-1.0f )
        },
        {   // left
            Vec3( 0.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 0.0f, 1.0f, 0.0f )
        },
        {   // back
            Vec3( 1.0f, 1.0f,-1.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 0.0f, 1.0f,-1.0f )
        },
        {   // front
            Vec3( 0.0f, 1.0f, 0.0f ),
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 0.0f, 0.0f ),
            Vec3( 1.0f, 1.0f, 0.0f )
        },
        {   // top
            Vec3( 1.0f, 1.0f, 0.0f ),
            Vec3( 1.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 1.0f,-1.0f ),
            Vec3( 0.0f, 1.0f, 0.0f )
        },
        {   // bottom
            Vec3( 0.0f, 0.0f, 0.0f ),
            Vec3( 0.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 0.0f,-1.0f ),
            Vec3( 1.0f, 0.0f, 0.0f )
        }
    };

    Vec3 CubeNormals[6] =
    {
        Vec3( 1.0f,  0.0f,  0.0f ),
        Vec3(-1.0f,  0.0f,  0.0f ),
        Vec3( 0.0f,  0.0f, -1.0f ),
        Vec3( 0.0f,  0.0f,  1.0f ),
        Vec3( 0.0f,  1.0f,  0.0f ),
        Vec3( 0.0f, -1.0f,  0.0f )
    };

    //
    // Directional mapper
    //   (in game space)
    //  1. +x   -->   right
    //  2. -x   -->   left
    //  3. +y   -->   back
    //  4. -y   -->   front
    //  5. +z   -->   top
    //  6. -z   -->   bottom
    //
    Vec3 axes[6] = { Vec3( 1.0f, 0.0f, 0.0f ),
                     Vec3(-1.0f, 0.0f, 0.0f ),
                     Vec3( 0.0f, 1.0f, 0.0f ),
                     Vec3( 0.0f,-1.0f, 0.0f ),
                     Vec3( 0.0f, 0.0f, 1.0f ),
                     Vec3( 0.0f, 0.0f,-1.0f ) };

    //
    // Okay, walk through each cube
    //
    std::vector<WorldCube>::const_iterator itr;
    int hiddenCubes = 0;
    int hiddenFaces = 0;
    int totalFaces  = 0;

    std::cout << "Starting compile" << std::endl;

    for ( itr = m_cubes.begin(); itr != m_cubes.end(); ++itr )
    {
        Point p = itr->position();

        //
        // Check each side of the cube to see if it has a neighbor
        //
        int hidden = 0;

        for ( int k = 0; k < 6; ++k )
        {
            totalFaces++;

            Point n = Point( static_cast<int>(p[0] + axes[k][0]),
                             static_cast<int>(p[1] + axes[k][1]),
                             static_cast<int>(p[2] + axes[k][2]) );
            Vec3  b = Vec3(  static_cast<float>(p[0]),
				             static_cast<float>(p[2]),
							 static_cast<float>(-p[1]) );

            if ( isEmptyAt( n ) )
            {
                // ADCB
                builder.addFace( b + CubePos[k][0], CubeNormals[k],
                                 b + CubePos[k][1], CubeNormals[k],
                                 b + CubePos[k][2], CubeNormals[k],
                                 b + CubePos[k][3], CubeNormals[k] );

                // Update faces optimized out
                hidden++;
            }
        }

        // Was the cube fully optimized out?
        if ( hidden == 6 ) { hiddenCubes++; }
        
        hiddenFaces += hidden;
    }

    std::cout << " ----- Chunk Statistics ---------------" << std::endl;
    std::cout << "  Cubes: "   << m_cubes.size() << " ("
              << hiddenCubes   << " hidden)"     << std::endl;
    std::cout << "  Sides: "   << totalFaces     << " ("
              << hiddenFaces   << " hidden, " << ( totalFaces-hiddenFaces )
              << " total)"     << std::endl;
    std::cout << "  Verts: "   << builder.numVerts()
              << ", Indices: " << builder.numIndices() << std::endl;

    return builder.createMesh();
}
*/

void WorldChunkBuilder::addCube( const Vec3& )
{

}

WorldChunkMesh WorldChunkBuilder::createMesh() const
{
    //
    // Create a vertex and index buffer to store geometry
    //
    const int vertexElementSize = 3*4 + 3*4 + 2*4; // f3f3f2 --> 32 bytes
    const int indexElementSize  = 3*4;             // i3     --> 12 bytes

    int vbsize = vertexElementSize * vertices.size();
    int ibsize = indexElementSize  * faces.size();

    uint32_t vbid = 0, ibid = 0;
/*
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
    */

    return WorldChunkMesh( vbid, ibid, faces.size() );
}

/**
 * A - D
 * | / |
 * B - C
 *
 * [BDA]
 * [BDC]
 */
void WorldChunkBuilder::addFace( const Vec3& pA, const Vec3& nA,
                const Vec3& pB, const Vec3& nB,
                const Vec3& pC, const Vec3& nC,
                const Vec3& pD, const Vec3& nD )
{
    vertices.push_back(CubeVertex( pA, nA, Vec3( 0.0, 0.0, 0.0 ) ));
    vertices.push_back(CubeVertex( pB, nB, Vec3( 0.0, 1.0, 0.0 ) ));
    vertices.push_back(CubeVertex( pC, nC, Vec3( 1.0, 1.0, 0.0 ) ));
    vertices.push_back(CubeVertex( pD, nD, Vec3( 1.0, 0.0, 0.0 ) ));

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

size_t WorldChunkBuilder::numIndices() const { return faces.size(); }
size_t WorldChunkBuilder::numFaces()   const { return faces.size() / 3; }
size_t WorldChunkBuilder::numVerts()   const { return faces.size(); }
