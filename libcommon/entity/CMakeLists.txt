###########################################################################
# Common code
###########################################################################
set(headers
        ${CMAKE_CURRENT_SOURCE_DIR}/component.h
        ${CMAKE_CURRENT_SOURCE_DIR}/entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/entitymanager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/defs.h
)

set(sources
        ${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/entitymanager.cpp
)

set(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/components.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_entitymanager.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
