# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project4_origin LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

add_library(${PROJECT_NAME}_mips32 SHARED
        mips32.cpp
        )
add_library(${PROJECT_NAME}_tac SHARED
        tac.cpp
        )

add_executable(${PROJECT_NAME}_main
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}_main
        ${PROJECT_NAME}_tac
        ${PROJECT_NAME}_mips32
        )
#IF (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
#    include(${CMAKE_SOURCE_DIR}/../cmake/preBuild.cmake)
#else ()
#    include(${CMAKE_SOURCE_DIR}/cmake/preBuild.cmake)
#endif ()
#FLEX_BISON_PRE_BUILD(${CMAKE_CURRENT_SOURCE_DIR}/src)
#
#add_executable(${PROJECT_NAME}_main src/main.cpp)
#
#set(dependenciesOfMain node yyerror_myself visitSyntaxTree type semanticError translate interCode)
#foreach (elementName IN LISTS dependenciesOfMain)
#    add_library(${PROJECT_NAME}_${elementName} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/${elementName}.cpp)
#    target_include_directories(${PROJECT_NAME}_${elementName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#    add_dependencies(${PROJECT_NAME}_${elementName} ${PROJECT_NAME}_empty)
#    MESSAGE(STATUS "${PROJECT_NAME}_${elementName} from src/${elementName}.cpp")
#    target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
#    add_dependencies(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
#endforeach ()
#unset(dependenciesOfMain)