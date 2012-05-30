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
#ifndef SCOTT_COMMON_LOGGING_LOGSTREAM_H
#define SCOTT_COMMON_LOGGING_LOGSTREAM_H

#include "logging.h"

#include <ostream>
#include <string>
#include <iostream>

// Forward declarations
template<typename Char, typename Traits = std::char_traits<char> >
class DebugStreambuf;

/**
 * Log stream class. This class extends the abstract IOStream ostream class
 * to turn it into a class capable of doing high level logging work.
 */
class LogStream : public std::ostream
{
public:
    LogStream( std::ostream *pConsoleStream, std::ofstream* pFileStream );
    ~LogStream();

    void setConsoleStream( std::ostream *pConsoleStream );
    void setFileStream( std::ofstream* pFileStream );

    void startLogEntry( const std::string& module, ELogLevel level );
    void endLogEntry();

private:
    DebugStreambuf<char>* mpStreambuf;
    std::ostream *mpConsoleStream;
    std::ofstream *mpFileStream;
};

#endif
