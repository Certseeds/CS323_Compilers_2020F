 # header begin
 cmake_minimum_required(VERSION 3.16.6)
 project(CS323_Compilers_project1 LANGUAGES CXX)

 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -Wextra")

 add_library(${PROJECT_NAME}_node
         ${CMAKE_CURRENT_SOURCE_DIR}/src/node.cpp
         )
