#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-10-17 17:33:45
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-29 22:36:03
### 
#!the SA said that symtab_ht has some error, so it do not need to do.
CMAKE_DIR="cmake-build-debug"
run_test() {
  python3 ./test.py
}
cmake_build_path(){
  if [[ -f "libsymtab.so" ]]; then
  rm "libsymtab.so"
  fi
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
cmake_pre(){
  cmake_build_path
  cd "${CMAKE_DIR}"
  cmake ..
  make -j "$(nproc)"
  cp ./libsymtab.so ./../libsymtab.so
  cd ..
  run_test
}
make_pre(){
  make clean
  make bttest
}
cmake_pre