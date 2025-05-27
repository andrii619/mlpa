function(add_clangtidy_to_target TARGET_NAME TARGET_HEADERS TARGET_INCLUDES)
    # file(GLOB_RECURSE ALL_TIDY_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
    # message("TIDY_HEADERS" ${ALL_TIDY_HEADERS})
    if(APPLE)
        set(STDLIB_FLAG "-stdlib=libc++")
    else()
        set(STDLIB_FLAG "-stdlib=libstdc++")
    endif()
    
    
    set(CLANG_TIDY_COMMAND clang-tidy --system-headers=false 
            -checks=readability-identifier-naming 
            --config-file=${CMAKE_SOURCE_DIR}/Tools/clang-tidy/clang-tidy.yaml 
            -extra-arg=${STDLIB_FLAG}
            -extra-arg=-I${CMAKE_SOURCE_DIR}/include 
            -extra-arg=-I${CMAKE_SOURCE_DIR}/utils
            -p=${CMAKE_BINARY_DIR} ${TARGET_HEADERS})
    message("TIDY-HEADER:" ${TIDY_HEADER_COMMAND})
    
    # add_custom_target(
    #     clang_tidy_headers
    #     COMMAND ${TIDY_HEADER_COMMAND}
    #     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    #     COMMENT "Running clang-tidy on headers for target ${TARGET_NAME}"
    #     VERBATIM
    # )
    
    set_target_properties(${TARGET_NAME} PROPERTIES C_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    
    # Ensure the main target depends on this running
endfunction()



# Function to create a clang-format target and run it before building the main target
function(add_clangformat_to_target TARGET_NAME TARGET_SOURCE_FILES)
    # Add a custom target for clang-format
    add_custom_target(
        ${TARGET_NAME}_clang-format
        COMMAND clang-format --Werror -i --style=file --fallback-style=Google --verbose ${TARGET_SOURCE_FILES}
        COMMENT "Running clang-format on all source files"
    )

    # Ensure the main target depends on this running
    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_clang-format)
endfunction()