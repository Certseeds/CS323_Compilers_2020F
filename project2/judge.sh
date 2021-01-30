#!/bin/bash
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-29 22:33:55
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
test_SID() {
  i=1
  folder="test"
  prefix="test_SID_"
  while [[ "${i}" -le "18" ]]; do
    is=$(printf "%02d" "${i}")
    echo "${is}"
    ./splc.out \
      ./"${folder}/${prefix}${is}".spl \
      >./"${folder}/${prefix}${is}".test 2>&1
    diff \
      "${folder}/${prefix}${is}".out \
      "${folder}/${prefix}${is}".test \
      -y --left-column --suppress-common-lines --suppress-common-lines
    i=$((i + 1))
  done
}
test_1() {
  i=1
  while [[ "${i}" -le "10" ]]; do
    is=$(printf "%02d" "${i}")
    echo "${is}"
    ./splc.out \
      ./test_1/test_1_r"${is}".spl \
      >./test_1/test_1_r"${is}".test 2>&1
    diff \
      ./test_1/test_1_r"${is}".out \
      ./test_1/test_1_r"${is}".test \
      -y --left-column --suppress-common-lines --suppress-common-lines
    i=$((i + 1))
  done
}
test_2() {
  i=1
  while [[ "${i}" -le "15" ]]; do
    is=$(printf "%02d" "${i}")
    echo "${is}"
    ./splc.out \
      ./test_2/test_2_r"${is}".spl \
      >./test_2/test_2_r"${is}".test 2>&1
    diff \
      ./test_2/test_2_r"${is}".out \
      ./test_2/test_2_r"${is}".test \
      -y --left-column --suppress-common-lines \
      --suppress-common-lines -W 200 i=$((i + 1))
  done
}
test_judge() {
  folder="./selected-anonym_after"
  cd "${folder}" || exit
  for i in *.spl; do
    [[ -e "${i}" ]] || break # handle the case of no *.wav files
    file_hash="${i:5:8}"
    echo "${file_hash}"
    if [[ -f "./test_${file_hash}.test" ]]; then
      rm "./test_${file_hash}.test"
      touch "./test_${file_hash}.test"
    fi
    ./../splc.out \
      ./test_"${file_hash}".spl \
      >./test_"${file_hash}".test 2>&1
    diff \
      ./test_"${file_hash}".out \
      ./test_"${file_hash}".test \
      -y --left-column --suppress-common-lines \
      --suppress-common-lines -W 200
  done
}
main() {
  if [[ -f "./splc.out" ]]; then
    rm ./splc.out
  fi
  make_steps
  test_SID
  #test_1
  #test_2
  #test_judge
  #new_feature
}
main