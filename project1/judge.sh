#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
# @LastEditors: nanoseeds
# @LastEditTime: 2020-10-02 19:50:45
###
CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
compiler() {
  cd "${CMAKE_DIR}"
  cmake ..
  make
  #-j "$(nproc)"
  cd ..
}
run_test() {
  ./${CMAKE_DIR}/Flex.out ./test/testcase1.in >./test/testcase1.test.out
  diff ./test/testcase1.test.out ./test/testcase1.data.out -y --left-column
}
cmake_ensure_dir
compiler
run_test
