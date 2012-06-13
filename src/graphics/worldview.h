/*
 * Copyright 2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SCOTT_CUBEWORLD_WORLD_VIEW_H
#define SCOTT_CUBEWORLD_WORLD_VIEW_H

#include <boost/noncopyable.hpp>
#include <vector>
#include "engine/point.h"
#include "graphics/renderprimitives.h"

class WorldChunk;
class IRenderer;

/**
 * Handles the platform independent drawing and event notifications for
 * the world
 */
class WorldView : boost::noncopyable
{
public:
    WorldView( IRenderer * pRenderer );
    ~WorldView();

    // Call this to inform the view that a worldchunk was been updated
    void chunkUpdated( const Point& position, WorldChunk * pChunk );

    // Call once a frame to rebuild chunks
    void update();

    // Convert a cube (in world coordinates) into a chunk's world space
    // origin
    static Point getChunkPosition( const Point& point );

private:
    struct ChunkViewData
    {
        Point position;
        ChunkRenderId id;
    };

    struct ChunkBuildData
    {
        Point position;
        WorldChunk * pChunk;
    };

private:
    IRenderer * mpRenderer;
    std::vector<ChunkViewData> mChunks;   // this is terrible
    std::vector<ChunkBuildData> mChunksToRebuild;
};

#endif
