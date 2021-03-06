#!/bin/bash
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-29 22:59:25
###
CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
compiler() {
  cd "${CMAKE_DIR}" || exit
  if [[ -f "Makefile" ]]; then
    make clean
  fi
  cmake ..
  make -j "$(nproc)"
  #cd ..
}
run_test() {
  # ./${CMAKE_DIR}/Flex.out ./test_prac/testcase1.in >./test_prac/testcase1.test_prac.out
  # diff ./test_prac/testcase1.test_prac.out ./test_prac/testcase1.data.out -y --left-column
  able=("01" "02" "05" "09" "12")
  for i in "${able[@]}"; do
    echo "${i}"
    ./CS323_Compilers_project1_pro1 ./../test_example/test_1_r"${i}".spl > \
      ./../test_example/test_1_r"${i}".test.out 2>&1
    diff ./../test_example/test_1_r"${i}".out ./../test_example/test_1_r"${i}".test.out \
      -y --left-column --suppress-common-lines
  done
}
basic_illgeal_test() {
  able2=("03" "04" "06" "07" "08" "10" "11")
  for i in "${able2[@]}"; do
    echo "${i}"
    ./CS323_Compilers_project1_pro1 ./../test_example/test_1_r"${i}".spl > \
      ./../test_example/test_1_r"${i}".test.out 2>&1
    diff ./../test_example/test_1_r"${i}".out ./../test_example/test_1_r"${i}".test.out \
      -y --left-column --suppress-common-lines --suppress-common-lines
  done
}
test_SID() {
  able3=("1" "2" "3" "4" "5")
  for i in "${able3[@]}"; do
    echo "${i}"
    ./CS323_Compilers_project1_pro1 ./../test/test_SID_"${i}".spl > \
      ./../test/test_SID_"${i}".test.out 2>&1
    diff ./../test/test_SID_"${i}".out ./../test/test_SID_"${i}".test.out \
      -y --left-column --suppress-common-lines --suppress-common-lines
  done
}
debug() {
  i="10"
  ./CS323_Compilers_project1_pro1 ./../test_example/test_1_r"${i}".spl > \
    ./../test_example/test_1_r"${i}".test.out 2>&1
  diff ./../test_example/test_"${i}".out ./../test_example/test_"${i}".test.out \
    -y --left-column --suppress-common-lines --suppress-common-lines
  exit
}
# echo
# make_file
# cmake_ensure_dir
# compiler
# debug
# run_test
# basic_illgeal_test
# test_SID
make_steps() {
  cd src || exit
  make clean
  make splc
  cp ./splc ./../splc
  mv ./../splc ./../splc.out
  make clean
  cd ..
}
make_file() {
  able=("01" "02" "05" "09" "12" "03" "04" "06" "07" "08" "10" "11")
  for i in "${able[@]}"; do
    echo "${i}"
    ./splc.out ./test_example/test_1_r"${i}".spl > \
      ./test_example/test_1_r"${i}".test.out 2>&1
    diff ./test_example/test_1_r"${i}".out ./test_example/test_1_r"${i}".test.out \
      -y --left-column --suppress-common-lines --suppress-common-lines
  done
}
make_test_stdoutput() {
  able=("1" "2" "3" "4" "5")
  for i in "${able[@]}"; do
    echo "${i}"
    ./splc.out ./test/test_SID_"${i}".spl > ./test/test_SID_"${i}".test.out 2>&1
  done
}
new_feature() {
    ./splc.out ./test/test_SID_2.spl
    ./splc.out ./test_example/test_1_r12.spl
}
make_steps
make_file
make_test_stdoutput
#new_feature
