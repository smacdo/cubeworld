# FindGoogleTest.cmake
# Copyright (c) 2010
#     Scott MacDonald <scott@whitespaceconsideredharmful.com>
#######################################################################
MACRO(GTEST_ADD_TESTS _testapp _testfilesA)
    SET(test_out_bin ${CMAKE_CURRENT_BINARY_DIR}/testrunner-${_testapp})
    SET(test_files   ${_testfilesA} ${ARGN})
    SET(runner_cpp   ${CMAKE_SOURCE_DIR}/extra/googletest/testrunner/googletest_main.cpp)

    ADD_CUSTOM_COMMAND(
        OUTPUT   ${test_out_bin}
        DEPENDS  ${test_files}
        COMMAND  ${test_out_bin}
    )

    SET_SOURCE_FILES_PROPERTIES(${test_out_bin} PROPERTIES GENERATED true)

    MESSAGE("Creating tests for: " ${test_files})
    ADD_EXECUTABLE( ${test_out_bin} ${runner_cpp} ${testfiles} )
ENDMACRO()
