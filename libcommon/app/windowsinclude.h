#include <app/platform.h>

#ifdef WINDOWS
#   ifndef WINDOWS_ALREADY_INCLUDED
#       define WINDOWS_LEAN_AND_MEAN
#       define NOMINMAX
#       define NOGDI
#       include <windows.h>
#   endif
#else
    // not a windows platform
#endif
