###########################################################################
# Common application code
###########################################################################
set(headers
    ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/stacktrace.h
)

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stacktrace.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("Using darwin platform (platform/darwin.mm)")
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/darwin.mm)
    set(found_platform_cpp true)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("Using windows xp platform (platform/xp.cpp)")
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/xp.cpp)
    set(found_platform_cpp true)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Using linux platform (platform/linux.cpp)")
    set(sources ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/linux.cpp)
    set(found_platform_cpp true)
endif()

if( NOT DEFINED found_platform_cpp )
    message( "Could not locate appropriate platform implementation" )
    message( SEND_ERROR "Please update libcommon/platform/CMakeFiles.txt" )
endif()

# Add subdirectory code into libcommon
set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
