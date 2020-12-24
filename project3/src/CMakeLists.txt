# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

add_custom_target(${PROJECT_NAME}_FLEX_BISON
        COMMAND ls
        COMMAND pwd
        COMMAND flex lex.l
        COMMAND bison -t -d -v syntax.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        BYPRODUCTS "syntax.tab.c"
        COMMENT "This command will be executed before building target ${PROJECT_NAME}_FLEX_BISON")

add_custom_target(${PROJECT_NAME}_empty)

add_dependencies(${PROJECT_NAME}_empty ${PROJECT_NAME}_FLEX_BISON)

add_library(${PROJECT_NAME}_node
        STATIC
        node.cpp)

add_library(${PROJECT_NAME}_yyerror_myself
        STATIC
        yyerror_myself.cpp)
add_library(${PROJECT_NAME}_semanticError
        STATIC
        semanticError.cpp
        )
set_source_files_properties(syntax.tab.c PROPERTIES LANGUAGE CXX)

add_library(${PROJECT_NAME}_type
        STATIC
        type.cpp
        )

add_library(${PROJECT_NAME}_interCode
        STATIC
        ./interCode.cpp)
add_library(${PROJECT_NAME}_translate
        STATIC
        ./translate.cpp)
add_library(${PROJECT_NAME}_visitSyntaxTree
        STATIC
        visitSyntaxTree.cpp)

add_executable(${PROJECT_NAME}_main main.cpp)

set_source_files_properties("syntax.tab.c" PROPERTIES GENERATED TRUE)

set(dependenciesOfMain node yyerror_myself visitSyntaxTree type semanticError translate interCode)

foreach (elementName IN LISTS dependenciesOfMain)
    target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
    add_dependencies(${PROJECT_NAME}_${elementName} ${PROJECT_NAME}_empty)
    add_dependencies(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
endforeach ()

# this file just work for clion's identify, do not use it compiler files