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
#ifndef SCOTT_WINDOW_H
#define SCOTT_WINDOW_H

#include <string>
#include <boost/utility.hpp>

/**
 * Platform independent window class
 */
class IWindow : boost::noncopyable
{
public:
    IWindow( const std::string& windowTitle,
             unsigned int width,
             unsigned int height );
    virtual ~IWindow();
    virtual void create() = 0;
    virtual void show() = 0;
    virtual bool processMessages() = 0;
    virtual void exit() = 0;

    bool didUserQuit() const;
    bool isPaused() const;
    bool isResizing() const;
    bool isMinimized() const;
    bool wasResized() const;

    void setMinimized( bool wasMinimized );
    void setMaximized( bool wasMaximized );
    void setResized( bool wasResized, unsigned int width=0, unsigned int height=0 );

    void clearResizedFlag();

    // Returns the name of the window
    std::string windowTitle() const;

    // Returns the width of the window
    unsigned int width() const;

    // Returns the height of the window
    unsigned int height() const;

protected:
    void setUserQuit();
    void setPaused( bool isPaused );
    void setResizing( bool isResizing );

private:
    std::string mTitle;
    unsigned int mWidth;
    unsigned int mHeight;

    bool mCreated;
    bool mUserQuit;
    bool mPaused;
    bool mResizing;
    bool mResizedFlag;
    bool mMinimized;
    bool mMaximized;
};

#endif
