#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-12-25 20:36:25
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-12-25 20:40:23
###
CMAKE_DIR="cmake-build-debug"
run_test() {
  ./Object.out ./data/1.json
  ./Object.out ./data/2.json
  ./Object.out ./data/3.json
}
cmake_build_path() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
cmake_build() {
  cmake_build_path
  cd "${CMAKE_DIR}"
  make clean
  cmake ..
  make -j "$(nproc)"
  cp ./Object.out ./../Object.out
  cd ..
  run_test
}
cmake_build
