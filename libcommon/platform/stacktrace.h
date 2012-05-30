#ifndef SCOTT_COMMON_PLATFORM_STACKTRACE_H
#define SCOTT_COMMON_PLATFORM_STACKTRACE_H

#include <vector>
#include <string>

/**
 * Returns an array of strings containing the running application's
 * current stack trace
 */
std::vector<std::string> GetStackTrace();

#endif
