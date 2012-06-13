#ifndef SCOTT_CUBEWORLD_GRAPHICS_RENDERER_H
#define SCOTT_CUBEWORLD_GRAPHICS_RENDERER_H

#include <boost/noncopyable.hpp>
#include <vector>

#include "graphics/renderprimitives.h"

class WorldChunk;

/**
 * Vendor neutral rendering interface
 */
class IRenderer : boost::noncopyable
{
public:
    virtual ~IRenderer() {}

    // Clears the viewport
    virtual void clear() = 0;

    // Draws the scene onto the front buffer
    virtual void present() = 0;

    // Draw a list of chunks as the world's background
    virtual void renderChunks(
            const std::vector<ChunkRenderId>& chunks ) = 0;

    // Upload a world chunk
    virtual ChunkRenderId uploadChunk( const WorldChunk& pChunk ) = 0;

private:
};

#endif
