###########################################################################
# Common code
###########################################################################
set(headers
        ${CMAKE_CURRENT_SOURCE_DIR}/delete.h
        ${CMAKE_CURRENT_SOURCE_DIR}/deref.h
        ${CMAKE_CURRENT_SOURCE_DIR}/macros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/noncopyable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/nullptr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scopedptr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/singleton.h
        ${CMAKE_CURRENT_SOURCE_DIR}/static_assert.h
        ${CMAKE_CURRENT_SOURCE_DIR}/time.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.h
)

set(sources
        ${CMAKE_CURRENT_SOURCE_DIR}/time.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/assert.cpp
)

set(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_delete.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_deref.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
