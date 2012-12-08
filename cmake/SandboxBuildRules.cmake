###
### Initializes google test
###
function(init_googletest)
    include_directories(${GTEST_PATH}/include)
endfunction()

###
### Takes a project name, and adds a set of useful command line make
### targets. These targets automate a bunch of common actions such as:
###   * r-NAME: run project NAME
###   * d-NAME: debug project NAME
###   * m-NAME: run valgrind memory test on NAME
###
function(add_standard_targets name)
    # Build runner
    add_custom_target(r-${name} ${CMAKE_CURRENT_BINARY_DIR}/${name}
                      DEPENDS ${name}
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    # GDB test
    add_custom_target(d-${name}
                      gdb `pwd`/${name} -d ${PROJECT_SOURCE_DIR} -cd ${PROJECT_SOURCE_DIR}
                      DEPENDS ${name}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                      COMMENT "Runs selected application with debugging")

    # Valgrind test
    add_custom_target(m-${name}
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/run_memgrind.sh
                                      ${CMAKE_CURRENT_BINARY_DIR}/${name}
        DEPENDS ${name})

    # Cachegrind (Valgrind) test
    add_custom_target(c-${name}
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/run_cachegrind.sh
                                       ${CMAKE_CURRENT_BINARY_DIR}/${name}
        DEPENDS ${name})

    # View assembly for file
    add_custom_target(asm-${name}
                      objdump CMakeFiles/${name}.dir/${name}.cpp.o -dl -M intel -S --no-show-raw-insn
                      DEPENDS ${name}
                      COMMENT "Shows assembly output for application")
endfunction()

###
### Creates a simple, no-nonsense application that is composed of a single
### .cpp file with the same name as the project
###
function(add_program name)
    add_executable(${name} ${ARGN})

    # Enable standard flags
    set_source_files_properties("${ARGN}" PROPERTIES
         COMPILE_FLAGS "${CXX_FLAGS} -g -ggdb")

    add_standard_targets(${name})   
endfunction()


###
### Creates an application with the provided name, libraries, include
### directories and flags. If you are providing a list of libraries, be
### sure to seperate each one with a semi-colon charcter
###   (eg, "SDL;SDL_ttf")
###
function(add_program_with name libs includes flags)
    add_executable(${name} ${ARGN})

    include_directories(${includes})

    foreach (lib ${libs})
        if ( lib MATCHES "[A-Za-z0-9]+" )
            target_link_libraries(${name} ${lib})
        endif()
    endforeach()

    # Enable standard flags
    set_source_files_properties(${ARGN} PROPERTIES
         COMPILE_FLAGS "${CXX_FLAGS} -ggdb ${flags}")

    add_standard_targets(${name})
endfunction()

###
### Creates a simple application that is driven by google test
###
function(add_program_with_test name)
    add_executable(${name} ${ARGN} ${GTEST_RUNNER_PATH})
    target_link_libraries(${name} googletest)

    include_directories(${GTEST_PATH}/include)

    # Enable standard flags
    set_source_files_properties(${name}.cpp PROPERTIES
         COMPILE_FLAGS "${CXX_FLAGS} -g -ggdb")

    add_standard_targets(${name})
endfunction()


###
### Creates a new workbench item, with tests driven by google test
###
function(add_simple_workbench_item name)
    add_program_with_test(${name} ${name}.cpp)
endfunction()

###
### Creates a new simple "one off" program command line program
###
function(add_simple_oneoff name)
    add_program(${name} ${name}.cpp)
endfunction()


function(add_oneoff name libs includes flags)
    add_program_with( "${name}" "${libs}" "${includes}" "${flags}" "${name}.cpp")
endfunction()
