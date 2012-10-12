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
#ifndef SCOTT_CUBEWORLD_IWORLD_GENERATION_H
#define SCOTT_CUBEWORLD_IWORLD_GENERATION_H

#include <boost/noncopyable.hpp>
class World;
class WorldView;

class IWorldGenerator : boost::noncopyable
{
public:
    virtual ~IWorldGenerator() { };

    virtual World* generate( unsigned int cols,
                             unsigned int rows,
                             unsigned int depth,
                             WorldView * pWorldView ) = 0;
private:
};

#endif
