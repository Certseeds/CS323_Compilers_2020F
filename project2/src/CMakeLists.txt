# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

add_library(node
        STATIC
        node.cpp)

add_library(yyerror_myself
        STATIC
        yyerror_myself.cpp)

set_source_files_properties(syntax.tab.c PROPERTIES LANGUAGE CXX)
add_library(parser
        STATIC
        ./syntax.tab.c)

add_library(type
        STATIC
        type.cpp
        )

add_library(visitSyntaxTree
        STATIC
        visitSyntaxTree.cpp)
add_library(visitSyntaxTree2
        STATIC
        visitSyntaxTree2.cpp)
add_executable(${PROJECT_NAME}_main main.cpp)
target_link_libraries(${PROJECT_NAME}_main
        node yyerror_myself parser visitSyntaxTree type
        )
SET_TARGET_PROPERTIES(parser PROPERTIES LINKER_LANGUAGE CXX)

# this file just work for clion's identify, do not use it compiler files