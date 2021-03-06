#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-12-25 20:36:25
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-29 22:59:15
###
CMAKE_DIR="cmake-build-debug"
run_test() {
   for file in ./data/* ; do
   echo "${file}"
   ./jc.out "${file}"
   done
}
cmake_build_path() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
cmake_build() {
  cmake_build_path
  cd "${CMAKE_DIR}"
  if [[ -f "Makefile" ]]; then
    make clean
  fi
  cmake ..
  make -j "$(nproc)"
  cp ./jc.out ./../jc.out
  cd ..
  run_test
}
cmake_build
