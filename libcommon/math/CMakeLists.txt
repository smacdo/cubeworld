###########################################################################
# Common math code
###########################################################################
set(headers
        ${CMAKE_CURRENT_SOURCE_DIR}/angle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/constants.h
        ${CMAKE_CURRENT_SOURCE_DIR}/conversion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/interpolation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/matrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/perlin.h
        ${CMAKE_CURRENT_SOURCE_DIR}/matrixutils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/quaternion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/random.h
        ${CMAKE_CURRENT_SOURCE_DIR}/rect.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tmatrix.h
        ${CMAKE_CURRENT_SOURCE_DIR}/util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vector.h
)

set(sources
        ${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)

set(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_angle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_conversions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_interpolation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_matrix4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_matrixutils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_vector2.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )

# Options
option( MATH_COMMON_TYPEDEFS
            "Allow error delta when comparing floats"
            on )
option( MATH_USE_FUZZY_EQUALS
            "Allow template types to have common typedefs"
            on )
option( MATH_USE_DOUBLES
            "Use doubles for floating point computation"
            off )
option( MATH_DEBUG_MODE
            "Enable extra assertions in math calculations (slow)"
            on )

# set up math config
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/config.h )
