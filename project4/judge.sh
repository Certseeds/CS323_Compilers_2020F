#!/bin/bash
set -euox pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
 # @LastEditors: nanoseeds
 # @LastEditTime: 2021-01-30 16:17:10
###
CMAKE_DIR="cmake-build-debug"
cmake_ensure_dir() {
  # now in /lab01
  if [[ ! -d "${CMAKE_DIR}" ]]; then
    mkdir "${CMAKE_DIR}"
  fi
}
make_steps() {
  make clean
  make splc
  mv ./splc ./splc.out
}
cmake_steps() {
  cmake_ensure_dir
  cd "${CMAKE_DIR}" || exit
  #make clean
  cmake ..
  make -j "$(nproc)"
  mv ./CS323_Compilers_project4_main ./../splc.out
  cd ..
}
test() {
  local i=1
  while [[ "${i}" -le "3" ]]; do
    readinFileName="test_4_r$(printf "%02d" "${i}")"
    ./splc.out \
      ./test/"${readinFileName}.spl" \
      >./test/"${readinFileName}.test.asm" 2>&1
    i=$((i + 1))
  done
  spim -file ./test/test_4_r01.test.asm
  echo "1" | spim -file ./test/test_4_r02.test.asm
  echo "0" | spim -file ./test/test_4_r02.test.asm
  echo "-1" | spim -file ./test/test_4_r02.test.asm
  spim -file ./test/test_4_r03.test.asm
}
main() {
  if [[ -f "./splc.out" ]]; then
    rm ./splc.out
  fi
  cmake_steps
  test
}
main
