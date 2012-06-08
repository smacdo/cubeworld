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
#include <app/platform.h>
#include <app/logging.h>
#include "graphics/null/nullwindow.h"
#include "graphics/null/nullrenderer.h"
#include "cubeworld.h"

/////////////////////////////////////////////////////////////////////////////
// Application entry point
/////////////////////////////////////////////////////////////////////////////
int main( int /*argc*/, char** /*argv*/ )
{
    // Make sure we call any platform specific start up code first. This will allow
    // us to initialize all core libraries and anything else the specific platform
    // may require
    App::startup();
    LOG_NOTICE("WinMain") << "Application has started";

    // Create an empty renderer and window
    NullWindow mainWindow;
    NullRenderer renderer;
    
    // Create the game client
    LOG_NOTICE("WinMain") << "Creating the game client";
    CubeWorldClient game( &mainWindow, &renderer );

    // Run the game
    LOG_NOTICE("WinMain") << "Starting the game";
    return game.run();
}
