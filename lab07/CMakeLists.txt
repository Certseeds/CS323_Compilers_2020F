# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

IF (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    include(${CMAKE_SOURCE_DIR}/../cmake/preBuild.cmake)
else ()
    include(${CMAKE_SOURCE_DIR}/cmake/preBuild.cmake)
endif ()

FLEX_BISON_PRE_BUILD(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME}_Object STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp)

add_library(${PROJECT_NAME}_parser STATIC ${CMAKE_CURRENT_SOURCE_DIR}/syntax.tab.c)

add_executable(Object.out ./main.cpp)

target_link_libraries(Object.out
        ${PROJECT_NAME}_Object
        ${PROJECT_NAME}_parser
        )
add_dependencies(${PROJECT_NAME}_parser ${PROJECT_NAME}_empty)
add_dependencies(${PROJECT_NAME}_Object ${PROJECT_NAME}_empty)

