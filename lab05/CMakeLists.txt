# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -fPIC")

set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/symtab_bt.c PROPERTIES LANGUAGE CXX)

add_library(symtab SHARED ${CMAKE_CURRENT_SOURCE_DIR}/symtab_bt.c)

# add_library(symtab
#         SHARED
#         symtab_ht.cpp)
# add_library(symtab
#         SHARED
#         symtab_ll.cpp)