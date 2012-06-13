#include "graphics/worldview.h"
#include "graphics/irenderer.h"
#include "graphics/renderprimitives.h"
#include "engine/point.h"
#include "engine/worldchunk.h"
#include <common/assert.h>
#include <common/delete.h>
#include <common/deref.h>

#include <vector>

WorldView::WorldView( IRenderer * pRenderer )
    : mpRenderer( pRenderer ),
      mChunks(),
      mChunksToRebuild()
{
}

WorldView::~WorldView()
{
    // don't delete the renderer, it is owned by the game engine
}

/**
 * Informs the worldview that the chunk has been updated, and that the view
 * should updated the stored mesh.
 *
 * \param  position  World view position of the cube (or one of) that was
 *                   changed in the chunk
 * \param  pChunk    Pointer to the chunk
 */
void WorldView::chunkUpdated( const Point& position, WorldChunk *pChunk )
{
    assert( pChunk != NULL && "Null chunks cannot exist" );

    // Has the chunk been marked dirty yet? If not, lets throw it
    // into the list of chunks that needs to be updated
    if (! pChunk->isRebuildingView() )
    {
        pChunk->setIsRebuildingView( true );

        // Add to queue of chunks to rebuild
        ChunkBuildData build;
        build.position = position;
        build.pChunk   = pChunk;

        mChunksToRebuild.push_back( build );
    }
}

/**
 * Called to let the world view do updating and chunk rebuilding
 */
void WorldView::update()
{
    for ( unsigned int i = 0; i < mChunksToRebuild.size(); ++i )
    {
        ChunkBuildData& build = mChunksToRebuild[i];

        // Convert the cube position into the chunk's upper left corner
        //  (basically, we need the chunk's origin in world space)
        Point chunkPos = getChunkPosition( build.position );

        // Compile the world chunk into a graphics mesh and instruct the engine
        // to upload it into the graphics card
        ChunkRenderId obj = mpRenderer->uploadChunk( deref(build.pChunk) );

        // Remove the old world chunk and replace it with the new one
        //   TODO: actually remove it
        ChunkViewData view { chunkPos, obj };
        mChunks.push_back( view );

        // Mark as rebuilt
        build.pChunk->setIsRebuildingView( false );
    }

    mChunksToRebuild.clear();
}

Point WorldView::getChunkPosition( const Point& pos )
{
    unsigned int x = pos.x / WorldChunk::TOTAL_COLS;
    unsigned int y = pos.y / WorldChunk::TOTAL_ROWS;
    unsigned int z = pos.z / WorldChunk::TOTAL_DEPTH;

    return Point( x * WorldChunk::TOTAL_COLS,
                  y * WorldChunk::TOTAL_ROWS,
                  z * WorldChunk::TOTAL_DEPTH );
}
