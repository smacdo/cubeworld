###########################################################################
# 3d common game code
###########################################################################
set(headers
        ${CMAKE_CURRENT_SOURCE_DIR}/boundingbox.h
        ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/defs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/fpscamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/frustum.h
        ${CMAKE_CURRENT_SOURCE_DIR}/intersection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/primitives.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.h
)

set(sources
        ${CMAKE_CURRENT_SOURCE_DIR}/boundingbox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/color.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frustum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/geoms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/intersectresult.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)

set(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_ray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_intersectionresult.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_color.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
