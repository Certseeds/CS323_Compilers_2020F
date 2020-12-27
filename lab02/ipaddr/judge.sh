#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-16 16:36:39
# @LastEditors: nanoseeds
# @LastEditTime: 2020-10-02 23:21:04
###
CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
compiler() {
  cd "${CMAKE_DIR}"
  make clean
  cmake ..
  make -j "$(nproc)"
  cd ..
}
run_test() {
  python3 ./ip_test.py
}
cmake_ensure_dir
compiler
run_test
