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
#include "graphics/null/nullwindow.h"

/**
 * Constructor
 */
NullWindow::NullWindow()
    : IWindow( "Null Window", 1, 1 )
{
}

/**
 * Destructor
 */
NullWindow::~NullWindow()
{

}

/**
 * Sets up the window description and have windows create it for us.
 */
void NullWindow::create()
{
}

/**
 * Show the window
 */
void NullWindow::show()
{
}

/**
 * Starts the application exit process
 */
void NullWindow::exit()
{
}

/**
 * Process any incoming window messages
 */
bool NullWindow::processMessages()
{
    return true;
}
