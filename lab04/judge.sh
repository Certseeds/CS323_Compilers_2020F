#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-09-23 01:30:40
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-09-30 01:18:58
### 
#! on work on ubuntu1804!

CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
compiler() {
  cd "${CMAKE_DIR}"
  cmake ..
  make -j "$(nproc)"
  cp ./jp.out ./../jp.out
  cd ..
}
run_test() {
  python3 ./jsonparser_test.py
}
cmake_ensure_dir
compiler
run_test
