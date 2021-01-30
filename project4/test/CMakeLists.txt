# header begin
cmake_minimum_required(VERSION 3.17.2)
project(CS323_Compilers_project4_test_cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ldl")


set(dependenciesOfMain 01 02 03)
foreach (elementName IN LISTS dependenciesOfMain)
    add_executable(${PROJECT_NAME}_test_4_r${elementName}
            ${CMAKE_CURRENT_SOURCE_DIR}/test_4_r${elementName}.cpp)
endforeach ()
unset(dependenciesOfMain)