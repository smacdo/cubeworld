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
#ifndef SCOTT_COMMON_LOGGING_H
#define SCOTT_COMMON_LOGGING_H

#include <ostream>
#include <string>
#include <boost/noncopyable.hpp>
#include <iostream>

/**
 * The logging severity level for a log entry
 */
enum ELogLevel
{
    ELOGLEVEL_TRACE,
    ELOGLEVEL_DEBUG,
    ELOGLEVEL_INFO,
    ELOGLEVEL_NOTICE,
    ELOGLEVEL_WARN,
    ELOGLEVEL_ERROR,
    ELOGLEVEL_FATAL,
    ELogLevel_Count
};

#include "app/logging_stream.h"

#define LOG_TRACE(x)  GlobalLog::getInstance().trace(x)
#define LOG_DEBUG(x)  GlobalLog::getInstance().debug(x)
#define LOG_INFO(x)   GlobalLog::getInstance().info(x)
#define LOG_NOTICE(x) GlobalLog::getInstance().notice(x)
#define LOG_WARN(x)   GlobalLog::getInstance().warn(x)
#define LOG_ERROR(x)  GlobalLog::getInstance().error(x)

extern const char* LOG_LEVEL_NAMES[ELogLevel_Count];

/**
 * The "magic" of the logging system. An instance of this class is returned
 * each time a call is made to GlobalLog::write(), which allows the caller
 * to stream anything interesting into the log entry for writing. As a great
 * bonus, the destructor (called at the end of that statement) will emit
 * new lines!
 */
class LogEntry
{
public:
    LogEntry( LogStream* debugStream );
    ~LogEntry();

    /**
     * Returns a iostreams instance that will emit output to the logging
     * interface rather than the generic STDOUT
     */
    template<typename T>
    std::ostream& operator << ( const T& obj )
    {
        (*mDebugStream) << obj;
        return *mDebugStream;
    }

private:
    LogEntry& operator = ( const LogEntry& );
    LogStream* mDebugStream;
};

/**
 * A object that can log information to files and the console
 */
class Log : boost::noncopyable
{
public:
    Log();
    Log( std::ostream *pConsoleStream, std::ofstream* pFileStream );
    ~Log();

    LogEntry trace( const std::string& system ) const;
    LogEntry debug( const std::string& system ) const;
    LogEntry info( const std::string& system ) const;
    LogEntry notice( const std::string& system ) const;
    LogEntry warn( const std::string& system ) const;
    LogEntry error( const std::string& system ) const;

    void setConsoleStream( std::ostream *pConsoleStream );
    void setFileStream( std::ofstream *pFileStream );

private:
    LogStream *mDebugStream;
};

/**
 * Logging singleton, used in conjunction with the logging macros
 */
class GlobalLog : boost::noncopyable
{
public:
    static void start();
    static Log& getInstance();

private:
    static Log mLog;
};



#endif
