###
### List of cmake functions
###
function(mkdoxygen name)
    add_custom_target( gendoc-${name}
                       COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                       COMMENT "Generate doxygen documentation for module")

    get_target_property(DOC_TARGET doc TYPE)

    if(NOT DOC_TARGET)
        add_custom_target(doc)
    endif()

    add_dependencies(doc gendoc-${name})
endfunction()
