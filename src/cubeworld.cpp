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
#include "cubeworld.h"
#include "graphics/iwindow.h"
#include "graphics/irenderer.h"

#include <common/assert.h>
#include <common/delete.h>
#include <common/time.h>

CubeWorldClient::CubeWorldClient( IWindow * pWindow,
                                  IRenderer * pRenderer )
    : GameClient( pWindow, pRenderer )
{
}

CubeWorldClient::~CubeWorldClient()
{
}

bool CubeWorldClient::initialize()
{
    return true;
}

bool CubeWorldClient::loadContent()
{
    return false;
}

void CubeWorldClient::unloadContent()
{

}

void CubeWorldClient::update( Time /*simTime*/, Time /*deltaTime*/ )
{

}

void CubeWorldClient::draw( Time /*simTime*/, float /*interpolation*/ )
{

}
