#!/bin/bash
set -eoux pipefail
###
# @Github: https://github.com/Certseeds/CS323_Compilers
# @Organization: SUSTech
# @Author: nanoseeds
# @Date: 2020-09-08 23:20:25
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-09-08 23:37:04
###
main() {
    dire="cmake-build-debug"
    if [ -d "${dire}" ]; then
        rm -rf "${dire}"
    fi
    if [[ ! -d "${dire}" ]]; then
        mkdir "${dire}"
    fi
    cd "${dire}"
    cmake ..
    make
    ./CS323_Compliers_lab01_hello.out
    ./CS323_Compliers_lab01_ll_main.out
    cd ..
    python3 ./ll_test.py
}

main
