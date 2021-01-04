# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab04_json LANGUAGES CXX)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lfl -ly")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

include(${CMAKE_SOURCE_DIR}/cmake/preBuild.cmake)
FLEX_BISON_PRE_BUILD(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(jp.out ${CMAKE_CURRENT_SOURCE_DIR}/syntax.tab.c)

SET_TARGET_PROPERTIES(jp.out PROPERTIES LINKER_LANGUAGE CXX)

add_dependencies(jp.out ${PROJECT_NAME}_empty)