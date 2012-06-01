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
#include "graphics/directx/dxwindow.h"
#include "graphics/directx/dxaboutbox.h"
#include <common/assert.h>
#include <common/delete.h>
#include "app/logging.h"
#include "resource.h"

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace {
/**
 * Converts an STL string into a WindowsNT wchar* wrapped inside of a
 * pretty wstring
 *
 * \param  str  The stl string you want to convert
 * \return A wstring representing the input
 */
std::wstring WinNTStringToWideString( const std::string& str )
{
    // Find the length of the soon to be allocated wstring
    size_t slen = str.length();
    int len     = MultiByteToWideChar( CP_ACP, 0,
                                        str.c_str(),
                                        static_cast<int>(slen) + 1,
                                        0,
                                        0 );

    // Allocate space for the new wstring, and then convert the input
    wchar_t *buffer = new wchar_t[len];

    MultiByteToWideChar( CP_ACP, 0,
                            str.c_str(),
                            static_cast<int>(slen) + 1,
                            buffer,
                            len );

    // Now create the wstring, copy the temporary wchar* buffer into it and
    // then destroy the buffer before returning
    std::wstring result( buffer );
    DeleteArray( buffer );

    return result;
}
}


/**
 * Constructor
 */
MainWindow::MainWindow( HINSTANCE hInstance,
                        const std::string& title,
                        unsigned int width,
                        unsigned int height )
    : IWindow( title, width, height ),
      mAppClassName( L"HailstormMainRenderWindow" ),
      mAppInstance( hInstance ),
      mWindowHandle( 0 )
{

}

/**
 * Destructor
 */
MainWindow::~MainWindow()
{

}

/**
 * Sets up the window description and have windows create it for us.
 */
void MainWindow::create()
{
    LOG_DEBUG("GUI") << "Creating the renderer main window";
    WNDCLASSEX wcex;

    // Configure the window description struct
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= mAppInstance;
    wcex.hIcon			= LoadIcon(mAppInstance, MAKEINTRESOURCE(IDI_DIRECTX));
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DIRECTX);
    wcex.lpszClassName	= mAppClassName.c_str();
    wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // Register the window class description
    ATOM result = RegisterClassEx(&wcex);
    assert( result != 0 );

    // Convert the UTF8 window title to Window's UTF16s
    std::wstring wideWindowTitle = WinNTStringToWideString( windowTitle() );

    // Need to find out how big to make the window, depending on the size of the
    // back buffer
    RECT windowRect = { 200, 200, 200 + width(), 200 + height() };
    AdjustWindowRectEx( &windowRect, WS_OVERLAPPEDWINDOW, TRUE, WS_EX_OVERLAPPEDWINDOW );

    // Now create the window
    HWND tempHwnd = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
        mAppClassName.c_str(),
        wideWindowTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        windowRect.left,
        windowRect.top,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        mAppInstance,
        this
        );

    // Verify that the window was created
    assert( mWindowHandle == tempHwnd );
    assert( mWindowHandle != NULL );
}

/**
 * Show the window
 */
void MainWindow::show()
{
    LOG_DEBUG("GUI") << "Showing the main window";
    assert( mWindowHandle != 0 );

    ShowWindow( mWindowHandle, SW_RESTORE );
    UpdateWindow( mWindowHandle );
}

/**
 * Starts the application exit process
 */
void MainWindow::exit()
{
    LOG_DEBUG("GUI") << "MainWindow::exit() has been called";
    setUserQuit();
    DestroyWindow( mWindowHandle );
}

/**
 * Show the about application message box
 */
void MainWindow::showAboutBox() const
{
    AboutBox about( appInstance(), windowHandle() );
    about.show();
}

/**
 * Return the handle of the main window
 */
HWND MainWindow::windowHandle() const
{
    return mWindowHandle;
}

/**
 * Sets the window handle that represents the main window
 */
void MainWindow::setWindowHandle( HWND hWnd )
{
    mWindowHandle = hWnd;
}

/**
 * Returns the application instance that owns the main window
 */
HINSTANCE MainWindow::appInstance() const
{
    return mAppInstance;
}

/**
 * Process any incoming window messages
 */
bool MainWindow::processMessages()
{
    MSG message;
    bool keepGoing = true;

    while ( keepGoing && PeekMessage( &message, mWindowHandle, 0, 0, PM_REMOVE ) == TRUE )
    {
        if ( message.message == WM_QUIT )
        {
            LOG_NOTICE("GUI") << "Quit received. Application is going to exit";
            keepGoing = false;
            setUserQuit();
        }

        TranslateMessage( &message );
        DispatchMessage( &message );
    }

    return keepGoing;
}

/**
 * Message loop handler
 */
LRESULT MainWindow::handleMessage( UINT message, WPARAM wParam, LPARAM lParam )
{
    HWND hWnd = windowHandle();
    int wmId, wmEvent;

    switch ( message )
    {
        case WM_COMMAND:
            wmId    = LOWORD( wParam );
            wmEvent = HIWORD( wParam );

            // Parse the menu selections:
            switch ( wmId )
            {
                case IDM_ABOUT:
                    showAboutBox();
                    break;
                case IDM_EXIT:
                    this->exit();
                    break;
                default:
                    return DefWindowProc( hWnd, message, wParam, lParam );
            }
            break;

        case WM_ACTIVATE:
            if ( LOWORD(wParam) == WA_INACTIVE )
            {
                setPaused( true );
            }
            else
            {
                setPaused( false );
            }
            break;

        case WM_SIZE:
            if ( wParam == SIZE_MINIMIZED )
            {
                setPaused( true );
                setMinimized( true );
            }
            else if ( wParam == SIZE_MAXIMIZED )
            {
                // Unpause if we are coming out of a minimize
                if ( isMinimized() )
                {
                    setPaused( false );
                    setMinimized( false );
                }

                setResized( true, LOWORD(lParam), HIWORD(lParam) );
            }
            else
            {
                // Unpause if we are coming out of a minimize
                if ( isMinimized() )
                {
                    setPaused( false );
                    setMinimized( false );
                }

                setResized( true, LOWORD(lParam), HIWORD(lParam) );
            }
            break;

        case WM_POWERBROADCAST:
            if ( wParam == PBT_APMQUERYSUSPEND )
            {
                // The application is about to be suspended. We should prepare for
                // this event by saving any data and then pausing the game loop
                // until we come out of suspension
            }
            else if ( wParam == PBT_APMRESUMESUSPEND )
            {
                // The application is being resumed from suspension. We should
                // reload any saved data and unpause the game loop
            }

        case WM_ENTERMENULOOP:
            // Pause while user is in menu
            setPaused( true );
            break;

        case WM_EXITMENULOOP:
            // Unpause after user has exited menu
            setPaused( false );
            break;

        case WM_ENTERSIZEMOVE:
            setResizing( true );
            setPaused( true );
            break;

        case WM_EXITSIZEMOVE:
            setResizing( false );
            setPaused( false );
            break;

        case WM_CLOSE:
            PostQuitMessage( 0 );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// Application message loop
/////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow * pMainWindow = NULL;

    //
    // Grab a pointer to the Window* instance that is sending this message.
    //  Either a window was created, in which case we need to save the pointer,
    //  or we need to look up the saved value
    //
    if ( message == WM_NCCREATE )
    {
        // We need to intercept the WM_NCCREATE message, since it is the first
        // message that a newly create window will send.  Once we get it, we will
        // grab the encoded Window* pointer and use SetWindowLong to save it for
        // future use
        LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>( lParam );
        pMainWindow       = reinterpret_cast<MainWindow*>( cs->lpCreateParams );
        assert( pMainWindow != NULL && "Failed to find window pointer");

        // Store the window pointer
        ::SetWindowLongPtr(
            hWnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>( pMainWindow ) );

        // Also store the assigned HWND value
        pMainWindow->setWindowHandle( hWnd );
    }
    else
    {
        // Try to look up the pointer that is stored in the window's userdata
        // field
        pMainWindow =
            reinterpret_cast<MainWindow*>( ::GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
    }

    // Route the message to the correct window instance. If we could not decipher
    // the instance, then just let windows perform a default action
    if ( pMainWindow != NULL )
    {
        return pMainWindow->handleMessage( message, wParam, lParam );
    }
    else
    {
        return DefWindowProc( hWnd, message, wParam, lParam );
    }


}