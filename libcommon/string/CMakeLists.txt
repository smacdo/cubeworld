###########################################################################
# Common string code
###########################################################################
set(includes
        ${CMAKE_CURRENT_SOURCE_DIR}/crc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/lcasts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/makestring.h
        ${CMAKE_CURRENT_SOURCE_DIR}/reftag.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sequenceformatter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stringbuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/util.h
)

set(sources
        ${CMAKE_CURRENT_SOURCE_DIR}/crc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/loadfile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/replace.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/streamprint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.cpp
)

set(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_crc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_tokenizer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_streamprint.cpp
)

set( libcommon_incs  ${libcommon_incs}  ${includes} PARENT_SCOPE )
set( libcommon_srcs  ${libcommon_srcs}  ${sources} PARENT_SCOPE )
set( libcommon_tests ${libcommon_tests} ${tests} PARENT_SCOPE )
