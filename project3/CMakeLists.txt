# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

FIND_PACKAGE(FLEX)
FIND_PACKAGE(BISON)
add_custom_target(${PROJECT_NAME}_FLEX_BISON
        COMMAND ls
        COMMAND pwd
        COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l
        COMMAND bison -t -d -v ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        BYPRODUCTS "syntax.tab.c"
        COMMENT "This command will be executed before building target ${PROJECT_NAME}_FLEX_BISON")

add_custom_target(${PROJECT_NAME}_empty)

add_dependencies(${PROJECT_NAME}_empty ${PROJECT_NAME}_FLEX_BISON)

set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/syntax.tab.c PROPERTIES LANGUAGE CXX GENERATED TRUE)


set(dependenciesOfMain node yyerror_myself visitSyntaxTree type semanticError translate interCode)

set_source_files_properties(src/syntax.tab.c PROPERTIES LANGUAGE CXX GENERATED TRUE)

add_executable(${PROJECT_NAME}_main src/main.cpp)

foreach (elementName IN LISTS dependenciesOfMain)
    add_library(${PROJECT_NAME}_${elementName} STATIC src/${elementName}.cpp)
    MESSAGE(STATUS "${PROJECT_NAME}_${elementName} from src/${elementName}.cpp")
    target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
    add_dependencies(${PROJECT_NAME}_${elementName} ${PROJECT_NAME}_empty)
    add_dependencies(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
endforeach ()

# this file just work for clion's identify, do not use it compiler files