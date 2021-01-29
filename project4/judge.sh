#!/bin/bash
set -euox pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers_2020F
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-19 17:59:07
# @LastEditors: nanoseeds
# @LastEditTime: 2020-12-12 21:40:49
###
make_steps() {
  make clean
  make splc
  mv ./splc ./splc.out
}
cmake_steps() {
  cd "cmake-build-debug" || exit
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
      >./test/"${readinFileName}.asm.test" 2>&1
    i=$((i + 1))
  done
}
main() {
  if [[ -f "./splc.out" ]]; then
    rm ./splc.out
  fi
  cmake_steps
  test
}
main
