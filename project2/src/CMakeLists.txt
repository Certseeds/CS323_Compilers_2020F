# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")

include(./../../cmake/preBuild.cmake)
FLEX_BISON_PRE_BUILD(${CMAKE_CURRENT_SOURCE_DIR})

set(dependenciesOfMain node yyerror_myself visitSyntaxTree type semanticError)

add_executable(${PROJECT_NAME}_main main.cpp)

foreach (elementName IN LISTS dependenciesOfMain)
    add_library(${PROJECT_NAME}_${elementName} STATIC ${elementName}.cpp)
    MESSAGE(STATUS "${PROJECT_NAME}_${elementName} from ${elementName}.cpp")
    target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
    add_dependencies(${PROJECT_NAME}_${elementName} ${PROJECT_NAME}_empty)
    add_dependencies(${PROJECT_NAME}_main ${PROJECT_NAME}_${elementName})
endforeach ()

# this file just work for clion's identify, do not use it compiler files