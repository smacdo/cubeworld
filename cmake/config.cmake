###
### Detect the OS
###
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("PLATFORM: Windows")
    set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("PLATFORM: Linux")
    set(LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("PLATFORM: Darwin")
    set(DARWIN 1)

    # attempt to detect OSX version
    EXEC_PROGRAM(/usr/bin/sw_vers ARGS -productVersion OUTPUT_VARIABLE MACOSX_VERSION_RAW)
    STRING(REGEX REPLACE "10\\.([0-9]).*" "\\1" MACOSX_VERSION "${MACOSX_VERSION_RAW}")

    # Refuse to run on an older Mac system
    if (${MACOSX_VERSION} LESS 6)
        message(WARNING "Unsupported version of OS X: ${MACOSX_VERSION_RAW}")
        return()
    endif()

    # Change the compiler to clang
else()
    message(WARNING "Unsupported operating system, assuming linux")
    set(LINUX 1)
endif()

###
### Detect the operating system
###
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    message("COMPILER: GCC compatible")
    set(COMPILER_GCC 1)
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-dumpversion" OUTPUT_VARIABLE GCC_VERSION_OUTPUT)
    string(REGEX REPLACE "([0-9]+\\.[0-9]+).*" "\\1" GCC_VERSION "${GCC_VERSION_OUTPUT}")
elseif(MSVC_VERSION EQUAL 1400)
    message(WARNING "Visual Studio 2005 is not supported")
    return()
elseif(MSVC_VERSION EQUAL 1500)
    message(WARNING "Visual Studio 2008 is not supported")
    return()
elseif(MSVC_VERSION EQUAL 1600)
    message("COMPILER: Visual Studio 2010+")
    set(COMPILER_MSVC 1)
else()
    message("COMPILER: Unknown (assuming GCC compatible)")
    set(COMPILER_GCC 1)
endif()

