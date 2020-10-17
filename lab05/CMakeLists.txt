# header begin
cmake_minimum_required(VERSION 3.16.6)
project(CS323_Compilers_lab05 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c11 -Wall -Wextra -fPIC")

add_library(symtab
        SHARED
        symtab_bt.c)
# add_library(symtab
#         SHARED
#         symtab_ht.cpp)  
# add_library(symtab
#         SHARED
#         symtab_ll.cpp)  