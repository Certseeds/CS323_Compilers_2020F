#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-10-02 23:30:54
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-10-02 23:36:01
### 
path=(
    lab01
    lab02/ipaddr
    lab02/wc
    lab03/calc
    lab03/parentheses
)
main(){
    for i in "${path[@]}"; do
        old_path=$(pwd)
        cd "${i}"
        ./judge.sh
        cd "${old_path}"
    done
}
main