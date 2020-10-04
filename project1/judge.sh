#!/bin/bash

###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-10-04 22:33:04
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
  #cd ..
}
run_test() {
  # ./${CMAKE_DIR}/Flex.out ./test/testcase1.in >./test/testcase1.test.out
  # diff ./test/testcase1.test.out ./test/testcase1.data.out -y --left-column
  able=("01" "02" "05" "09" "12")
  for i in "${able[@]}"; do
    echo "${i}"
    ./CS323_Compilers_project1_pro1 ./../test/test_1_r"${i}".spl > \
      ./../test/test_1_r"${i}".test.out 2>&1
    diff ./../test/test_1_r"${i}".out ./../test/test_1_r"${i}".test.out \
      -y --left-column
  done

  # TODO deal with the `0xabc` for char
}
basic_illgeal_test() {
  able2=("03" "04" "06" "07" "08" "10" "11")
  for i in "${able2[@]}"; do
    echo "${i}"
    ./CS323_Compilers_project1_pro1 ./../test/test_1_r"${i}".spl > \
      ./../test/test_1_r"${i}".test.out 2>&1
    diff ./../test/test_1_r"${i}".out ./../test/test_1_r"${i}".test.out \
      -y --left-column
  done
}
debug() {
  i="08"
  ./CS323_Compilers_project1_pro1 ./../test/test_1_r${i}.spl
  exit
}
echo
cmake_ensure_dir
compiler
#debug
run_test
basic_illgeal_test
