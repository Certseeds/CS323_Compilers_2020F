#!/bin/bash
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
# @LastEditors: nanoseeds
# @LastEditTime: 2020-11-06 11:23:53
###
make_steps() {
  cd src || exit
  make clean
  make splc
  cp ./splc ./../splc
  mv ./../splc ./../splc.out
  make clean
  cd ..
}
test_1() {
  able=("01" "02" "05" "09" "12" "03" "04" "06" "07" "08" "10" "11")
  for i in "${able[@]}"; do
    echo "${i}"
    ./splc.out ./test_1/test_1_r"${i}".spl >./test_1/test_1_r"${i}".test 2>&1
    diff ./test_1/test_1_r"${i}".out ./test_1/test_1_r"${i}".test \
      -y --left-column --suppress-common-lines --suppress-common-lines
  done
}
test_2() {
  able=("01" "02" "05" "09" "12" "03" "04" "06" "07" "08" "10" "11" "13" "14" "15")
  for i in "${able[@]}"; do
    echo "${i}"
    ./splc.out ./test_2/test_2_r"${i}".spl >./test_2/test_2_r"${i}".test 2>&1
    diff ./test_2/test_2_r"${i}".out ./test_2/test_2_r"${i}".test \
      -y --left-column --suppress-common-lines --suppress-common-lines
  done
}
rm ./splc.out
make_steps
#test_1
test_2
#new_feature
