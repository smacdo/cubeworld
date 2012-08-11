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
)

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/globallog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logentry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logstream.cpp
)

set(tests
        )

# Add subdirectory code into libcommon
set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
