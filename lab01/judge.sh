#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-08 23:20:25
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-29 22:57:13
###
CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  # now in /lab01
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
compiler() {
  # still in /lab01
  cd "${CMAKE_DIR}"
  if [[ -f "Makefile" ]]; then
    make clean
  fi
  cmake ..
  make -j "$(nproc)"
  ./CS323_Compilers_lab01_hello.out
  ./CS323_Compilers_lab01_ll_main.out
  cd ..
}

run_test() {
  # now in /lab01
  python3 ./ll_test.py
}
cmake_ensure_dir
compiler
run_test
