#include <app/debug.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace Debug;

void Break()
{
    // DebugBreak();
}

bool IsDebuggerPresent()
{
    // define the _WIN32_WINNT macro as 0x0400
//#ifdef WINDOWS
//    return IsDebuggerPresent();
//#else
    // ...
//    return false;
//#endif
    return false;
}

void PrintString( const std::string& message )
{
    PrintString( message.c_str() );
}
