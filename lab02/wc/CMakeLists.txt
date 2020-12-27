# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab02_wc LANGUAGES CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lfl -std=c11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

include(./../../cmake/preBuild.cmake)
FLEX_PRE_BUILD(CXX)

add_executable(wc.out ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c)

SET_TARGET_PROPERTIES(wc.out PROPERTIES LINKER_LANGUAGE CXX)

add_dependencies(wc.out ${PROJECT_NAME}_empty)

