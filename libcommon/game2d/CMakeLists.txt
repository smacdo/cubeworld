#########################################################################
# 2d game
#########################################################################
set(headers
    ${CMAKE_CURRENT_SOURCE_DIR}/fixedgrid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/point.h
)

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp
)

set(tests
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_fixedgrid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_point.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
