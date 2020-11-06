# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab04_json LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lfl -ly")
# -fPIC
FIND_PACKAGE(FLEX REQUIRED)
FIND_PACKAGE(BISON REQUIRED)
FLEX_TARGET(lexer
        lex.l ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c)
BISON_TARGET(parser
        syntax.y ${CMAKE_CURRENT_SOURCE_DIR}/syntax.tab.c)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)


ADD_LIBRARY(useless
        SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c
        )

add_executable(
        jp.out
        ./syntax.tab.c)

# ADD_LIBRARY(useless2
#      SHARED
#      ${CMAKE_SOURCE_DIR}/syntax.tab.c
# )
# TARGET_LINK_LIBRARIES(useless2 useless)
TARGET_LINK_LIBRARIES(jp.out useless)
