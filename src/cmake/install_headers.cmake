
macro(install_headers_with_directory INCLUDE_DIR HEADER_LIST)

    foreach(HEADER ${${HEADER_LIST}})
        string(REGEX MATCH ".*/" DIR ${HEADER})
        install(FILES ${HEADER} DESTINATION ${INCLUDE_DIR}/${DIR})
    endforeach(HEADER)

endmacro(install_headers_with_directory)
