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
#ifndef SCOTT_GAME_CLIENT_H
#define SCOTT_GAME_CLIENT_H

#include "engine/gametime.h"
#include <common/time.h>
#include <boost/noncopyable.hpp>

class IWindow;
class IRenderer;
class IWorldView;

/**
 * This is the foundation class for a hailstorm game client. A custom game
 * shall inherit from this class to provide custom game play and functionality
 */
class GameClient : boost::noncopyable
{
public:
    GameClient( IWindow *pMainWindow, IRenderer *pRenderer );
    virtual ~GameClient();

    int run();
    void setUpdateFrequency( int numUpdatesPerSecond );

protected:
    virtual bool initialize() = 0;
    virtual bool loadContent() = 0;
    virtual void unloadContent() = 0;
    virtual void update( Time simulationTime, Time deltaTime ) = 0;
    virtual void draw( Time simulationTime, float interpolation ) = 0;

private:
    int runMainGameLoop();
    TimeT getCurrentTime() const;
    void calculateSystemTimerFrequency();
    bool initializeClient();

protected:
    /// Pointer to the main rendering window
    IWindow * mpMainWindow;

    /// Pointer to the graphics renderer
    IRenderer * mpRenderer;

    /// Flag if the game is game loop is running
    bool mIsGameRunning;

    /// Flag if the game is running slowly (needing multiple updates to catch up)
    bool mIsRunningSlowly;

    /// Number of times to run the update method per second
    Time mUpdateFrequency;

    /// Estimated maximum skew for the internal windows sleep command
    Time mMaximumSleepSkew;
};

#endif
