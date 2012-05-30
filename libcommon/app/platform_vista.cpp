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
#define UNICODE
#define _UNICODE

#include "common/platform.h"
#include "common/logging.h"
#include "common/utils.h"
#include "config.h"
#include <string>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Commctrl.h>

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

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

namespace App {

/**
 * Generates a assertion reporting dialog (or console output) to show to the
 * player, before exiting the application
 *
 * \param  message     An accompanying assertion description (if provided)
 * \param  expression  String containing the expression text
 * \param  filename    Name of the file that generated the assertion
 * \param  lineNumber  Line that generated the assertion
 */
EAssertionStatus reportAssertion( const std::string& message,
                                  const std::string& expression,
                                  const std::string& filename,
                                  unsigned int lineNumber )
{
    HWND window = GetActiveWindow();

    // Write out an error message if none was given
    if ( message == NULL )
    {
        message = "Unlucky for you, an internal assertion check has failed. Please "
                  "contact the maintainer to let him know the game broke. ";
    }

    // Spit the assertion information out to the log
    LOG_ERROR("SYSTEM") << "ASSERTION FAILED in file "
                        << filename << ":" << lineNumber << "; "
                        << "assert( " << expression << " )";

    // Properly format the assertion message, and also convert the expression
    // and filename into wstring for display with windows
    std::ostringstream ss;

    ss << "ASSERTION DETAILS: \n"
       << "assert( " << expression << " )\n"
       << filename   << ":"        << lineNumber;

    // Convert the error message and assertion expression into Windows friendly
    // unicode wstring objects
    std::wstring wExpression = WinNTStringToWideString( ss.str() );
    std::wstring wMessage    = WinNTStringToWideString( message );

    // Set up variables required to display the task dialog
    TASKDIALOGCONFIG tc = { 0 };

    const TASKDIALOG_BUTTON cb[] =
    {
        { 0, L"View crash information\nThat way the developers can try to fix your bug"    },
        { 1, L"Fire up the debugger\nThis won't do anything unless you're a developer, sorry!" },
        { 2, L"Quit the game\nOh no! We promise not to crash again..."        }
    };

    tc.cbSize = sizeof( tc );
    tc.hwndParent = window;
    tc.hInstance  = (HINSTANCE) GetModuleHandle(NULL); //GetWindowLong( window, GWL_HINSTANCE );
    tc.dwFlags    = TDF_USE_HICON_MAIN | TDF_USE_HICON_FOOTER | TDF_EXPAND_FOOTER_AREA |
                    TDF_EXPANDED_BY_DEFAULT | TDF_USE_COMMAND_LINKS;

    LoadIconWithScaleDown( NULL, IDI_ERROR,
                           GetSystemMetrics(SM_CXICON),
                           GetSystemMetrics(SM_CYICON),
                           &tc.hMainIcon );
    LoadIconWithScaleDown( NULL, IDI_INFORMATION,
                           GetSystemMetrics(SM_CXSMICON),
                           GetSystemMetrics(SM_CYSMICON),
                           &tc.hFooterIcon);

    tc.pszWindowTitle      = L"Dungeon Crawler Internal Error";
    tc.pszMainInstruction  = L"An internal assertion check failed!";
    tc.pszContent          = L"Sorry to ruin your fun, but it looks like you found a bug in our code. Aren't you the lucky one?";
    tc.pszFooter           = wExpression.c_str();


    tc.cButtons       = ARRAYSIZE(cb);
    tc.pButtons       = cb;
    tc.nDefaultButton = 0;

    // Display the task dialog
    int buttonPressed        = 0;
    int commandPressed       = 0;
    BOOL verificationChecked = false;

    HRESULT hResult = TaskDialogIndirect( &tc,
                                          &buttonPressed, &commandPressed, 
                                          &verificationChecked );

    if (! SUCCEEDED(hResult) )
    {
        // huh?
        quit( EPROGRAM_ASSERT_FAILED, "Task dialog failed to display" );
    }

    // Now interpret the results of the task dialog
    switch ( buttonPressed )
    {
        case 0:     // view bug information
            quit( EPROGRAM_ASSERT_FAILED, "Assertion failed" );
            break;

        case 1:     // fire up debugger
            return EAssertion_Halt;
            
        case 2:     // quit
            quit( EPROGRAM_ASSERT_FAILED, "Assertion failed" );
            break;

        default:
            break;
    }

    // Now return and let the caller know that they should abort
    return EAssertion_Halt;
}

/**
 * Platform specific error reporting utility. This method is called by the
 * game engine whenever there is an error (or warning) to be reported. The
 * method is responsible for providing this information to the user and 
 * allowing the player to take appropriate action based on it.
 *
 * \param  message       A terse description of the error that occurred
 * \param  details       Optional contextual details of the error
 * \param  type          What type of error is this
 * \param  lineNumber    Line number that this error occurred on
 * \param  functionName  Name of the function where error occurred
 */
void raiseError( const std::string& message,
                 const std::string& details,
                 EErrorType type,
                 unsigned int lineNumber,
                 const char * filename,
                 const char * functionName )
{
    // Convert STL strings into wstrings for windows
    std::wstring wMessage     = WinNTStringToWideString( message );
    std::wstring wDetails     = WinNTStringToWideString( details );

    TASKDIALOGCONFIG tc = { 0 };

    const TASKDIALOG_BUTTON cb[] =
    {
        { 0, L"Keep going\nContinue playing, but please be aware the game could become instable"    },
        { 1, L"Quit the game\nRather than continuing onward, quit and fix the problem" }
    };

    tc.cbSize = sizeof( tc );
    tc.hwndParent = GetActiveWindow();
    tc.hInstance  = (HINSTANCE) GetModuleHandle(NULL);
    tc.dwFlags    = TDF_USE_HICON_MAIN | TDF_USE_COMMAND_LINKS |
                    TDF_EXPAND_FOOTER_AREA ;

    tc.cButtons       = ARRAYSIZE(cb);
    tc.pButtons       = cb;
    tc.nDefaultButton = 1;

    LoadIconWithScaleDown( NULL, IDI_ERROR,
        GetSystemMetrics(SM_CXICON),
        GetSystemMetrics(SM_CYICON),
        &tc.hMainIcon );

    tc.pszWindowTitle      = L"Dungeon Crawler Game Error";
    tc.pszMainInstruction  = L"The game has encountered a problem";
    tc.pszContent          = wMessage.c_str();

    if ( wDetails.size() > 0 )
    {
        tc.pszExpandedInformation  = wDetails.c_str();
        tc.pszExpandedControlText  = L"Hide error details";
        tc.pszCollapsedControlText = L"Show error details";
    }

    // Display the task dialog
    int buttonPressed        = 0;
    int commandPressed       = 0;
    BOOL verificationChecked = false;

    HRESULT hResult = TaskDialogIndirect( &tc,
        &buttonPressed, &commandPressed, 
        &verificationChecked );

    // Now interpret the results of the task dialog
    switch ( buttonPressed )
    {
    case 1:     // view bug information
        quit( EPROGRAM_USER_ERROR, "User chose to quit after error" );
        break;

    default:
        break;
    }
}

}
