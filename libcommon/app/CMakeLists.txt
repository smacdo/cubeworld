###########################################################################
# Common application code
###########################################################################
set(headers
    ${CMAKE_CURRENT_SOURCE_DIR}/app.h
    ${CMAKE_CURRENT_SOURCE_DIR}/debug.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_debugstreambuf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_debugstreambuf.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_stream.h
    ${CMAKE_CURRENT_SOURCE_DIR}/osplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/windowsinclude.h
)

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/globallog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logentry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logstream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(app_srcs ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/platform_darwin.mm)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET(app_srcs ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/platform_xp.cpp)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(app_srcs ${sources} ${CMAKE_CURRENT_SOURCE_DIR}/platform_unix.cpp)
endif()

set(tests
        )

# Add subdirectory code into libcommon
set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
