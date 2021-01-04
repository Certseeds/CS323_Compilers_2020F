# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab02_ipaddr LANGUAGES CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -std=c11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include(${CMAKE_SOURCE_DIR}/cmake/preBuild.cmake)
FLEX_PRE_BUILD(CXX)

ADD_LIBRARY(${PROJECT_NAME}_ip SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c)

SET_TARGET_PROPERTIES(${PROJECT_NAME}_ip PROPERTIES LINKER_LANGUAGE CXX)

add_dependencies(${PROJECT_NAME}_ip ${PROJECT_NAME}_empty)

