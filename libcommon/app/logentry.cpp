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
#include "app/logging.h"
#include "app/logging_debugstreambuf.h"
#include "app/logging_stream.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

/**
 * Log entry constructor. Takes two output streams and assigns them to
 * be the console output, and file output streams. Will also print a short
 * entry header consisting of the log level and component before returning
 *
 * \param  debugStream
 */
LogEntry::LogEntry( LogStream* debugStream )
    : mDebugStream( debugStream )      
{
}

/**
 * LogEntry destructor. Cleans up and emits end of line notices to the
 * log entry's streams
 */
LogEntry::~LogEntry()
{
    mDebugStream->endLogEntry();
}
