function(FLEX_PRE_BUILD language)
    FIND_PACKAGE(FLEX REQUIRED)
    add_custom_target(${PROJECT_NAME}_FLEX
            COMMAND ls
            COMMAND pwd
            COMMAND flex lex.l
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            BYPRODUCTS "lex.yy.c"
            COMMENT "This command will be executed before building target ${PROJECT_NAME}_FLEX")

    add_custom_target(${PROJECT_NAME}_empty)

    add_dependencies(${PROJECT_NAME}_empty ${PROJECT_NAME}_FLEX)

    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c PROPERTIES LANGUAGE ${language} GENERATED TRUE)
endfunction()
function(FLEX_BISON_PRE_BUILD FLEX_BISON_WORKING_PATH)
    FIND_PACKAGE(FLEX REQUIRED)
    FIND_PACKAGE(BISON REQUIRED)
    add_custom_target(${PROJECT_NAME}_FLEX_BISON
            COMMAND ls
            COMMAND pwd
            COMMAND flex lex.l
            COMMAND bison -t -d -v syntax.y
            WORKING_DIRECTORY ${FLEX_BISON_WORKING_PATH}
            BYPRODUCTS "syntax.tab.c"
            COMMENT "This command will be executed before building target ${PROJECT_NAME}_FLEX_BISON \n WIll BUILD IN WORKING_DIRECTORY ${FLEX_BISON_WORKING_PATH}")
    add_custom_target(${PROJECT_NAME}_empty)

    add_dependencies(${PROJECT_NAME}_empty ${PROJECT_NAME}_FLEX_BISON)

    set_source_files_properties(${FLEX_BISON_WORKING_PATH}/syntax.tab.c PROPERTIES LANGUAGE CXX GENERATED TRUE)
endfunction()