#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-12-12 21:22:01
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-12-12 21:50:41
###
main() {
  i=11
  while [[ "${i}" -le "18" ]]; do
    is=$(printf "%02d" "${i}")
    echo "${is}"
    touch "test_SID_${is}.spl"
    touch "test_SID_${is}.out"
    i=$((i + 1))
  done
}
main