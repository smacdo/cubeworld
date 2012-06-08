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
//#include "stdafx.h"
#include "graphics/iwindow.h"
#include "app/logging.h"

#include <string>
#include <cassert>

/**
 * Default constructor
 */
IWindow::IWindow( const std::string& title,
                  unsigned int width,
                  unsigned int height )
    : mTitle( title ),
      mWidth( width ),
      mHeight( height ),
      mUserQuit( false ),
      mPaused( false ),
      mResizing( false ),
      mResizedFlag( false ),
      mMinimized( false ),
      mMaximized( false )
{
}

/**
 * Window interface destructor
 */
IWindow::~IWindow()
{
}

/**
 * Checks if the user wants to quit the application
 */
bool  IWindow::didUserQuit() const
{
    return mUserQuit;
}

/**
 * Sets a flag saying that the user would like to quit the application
 */
void IWindow::setUserQuit()
{
    LOG_NOTICE("Window") << "setUserQuit has been called";
    mUserQuit = true;
}

/**
 * Checks if the window is "paused". A paused window is one that is not currently
 * receiving focus, and should therefore not be running the game.
 */
bool IWindow::isPaused() const
{
    return mPaused;
}

/**
 * Pauses or unpauses the main window
 */
void IWindow::setPaused( bool isPaused )
{
    LOG_NOTICE("Window")
        << "Window has been " << ( isPaused ? "paused" : "unpaused" );

    mPaused = isPaused;
}

/**
 * Checks if the window is in the middle of being resized
 */
bool IWindow::isResizing() const
{
    return mResizing;
}

/**
 * Places the window in resizing mode or tells the window it is no longer being
 * resized
 */
void IWindow::setResizing( bool isResizing )
{
    // Save the state of resizing
    mResizing = isResizing;
}

/**
 * Informs the window that it was resized
 */
void IWindow::setResized( bool wasResized, unsigned int width, unsigned int height )
{
    mResizedFlag = wasResized;

    // If the window was resized, then save the new width and height of the window
    if ( mResizedFlag )
    {
        assert( width  > 0 && "Window width cannot be zero" );
        assert( height > 0 && "Window height cannot be zero" );

        mWidth  = width;
        mHeight = height;
    }
}

/**
 * Checks if the window was resized
 */
bool IWindow::wasResized() const
{
    return mResizedFlag;
}

/**
 * Resets the resized flag to false
 */
void IWindow::clearResizedFlag()
{
    LOG_TRACE("Window") << "Cleared window resized flag";
    mResizedFlag = false;
}

/**
 * Sets or unsets the window's minimized state
 */
void IWindow::setMinimized( bool isMinimized )
{
    if ( isMinimized )
    {
        LOG_DEBUG("Window") << "Window minimized";
    }
    
    mMinimized = isMinimized;
}

/**
 * Checks if the window is minimized or not
 */
bool IWindow::isMinimized() const
{
    return mMinimized;
}

/**
 * Sets or unsets the window's maximized state
 */
void IWindow::setMaximized( bool isMaximized )
{
    if ( isMaximized )
    {
        LOG_DEBUG("Window") << "Window maximized";
    }

    mMaximized = isMaximized;
}

/**
 * Returns the window title
 */
std::string IWindow::windowTitle() const
{
    return mTitle;
}

/**
 * Returns the width of the window
 */
unsigned int IWindow::width() const
{
    return mWidth;
}

/**
 * Returns the height of the window
 */
unsigned int IWindow::height() const
{
    return mHeight;
}
