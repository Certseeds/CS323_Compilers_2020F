# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -std=c11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(ListOfFileNames linked_list.c hello_world.c main.c)
foreach (Element IN LISTS ListOfFileNames)
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/${Element} PROPERTIES LANGUAGE CXX GENERATED TRUE)
endforeach ()
add_library(${PROJECT_NAME}_ll SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/linked_list.c)

add_executable(${PROJECT_NAME}_hello.out
        ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.c)

add_executable(${PROJECT_NAME}_ll_main.out
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

target_link_libraries(${PROJECT_NAME}_ll_main.out ${PROJECT_NAME}_ll)