#include "graphics/worldview.h"
#include "engine/worldchunk.h"

#include <iostream>

WorldView::WorldView()
{
}

WorldView::~WorldView()
{
}

void WorldView::chunkUpdated( const WorldChunk * /*pChunk */ )
{
//    std::cout << "chunk updated" << std::endl;
}
