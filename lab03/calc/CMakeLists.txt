# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab03_calc LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -lfl ")

FIND_PACKAGE(FLEX REQUIRED)
FIND_PACKAGE(BISON REQUIRED)

FLEX_TARGET(lexer
        lex.l
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
BISON_TARGET(parser
        syntax.y
        ${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.c
        COMPILE_FLAGS "-t -d")

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

SET(GEN_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
        ${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.c
        ${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.h
        )
SET_SOURCE_FILES_PROPERTIES(${GEN_SOURCES} GENERATED)

ADD_LIBRARY(${PROJECT_NAME}_lexer
        SHARED
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
        )
ADD_LIBRARY(${PROJECT_NAME}_calc
        SHARED
        ${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.c
        ${CMAKE_CURRENT_SOURCE_DIR}/syntax.y
        )

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_calc ${PROJECT_NAME}_lexer)
