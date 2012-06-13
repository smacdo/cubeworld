/*
 * Copyright 2011 Scott MacDonald
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
#include "graphics/null/nullrenderer.h"
#include "graphics/renderprimitives.h"
#include "engine/worldchunk.h"
#include <vector>

NullRenderer::NullRenderer()
{

}

NullRenderer::~NullRenderer()
{

}

void NullRenderer::clear()
{

}

void NullRenderer::present()
{

}

void NullRenderer::renderChunks( const std::vector<ChunkRenderId>& )
{

}

ChunkRenderId NullRenderer::uploadChunk( const WorldChunk& )
{
    return 0u;
}
