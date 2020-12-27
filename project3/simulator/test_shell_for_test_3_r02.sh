#!/bin/bash
set -eoux pipefail
###
 # @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 # @Organization: SUSTech
 # @Author: nanoseeds
 # @Date: 2020-12-22 16:38:06
 # @LastEditors: nanoseeds
 # @LastEditTime: 2020-12-22 16:43:45
### 
echo "year is ${1}"
echo "month 2"
./irsim ./../test/test_3_r02.ir.test -i "${1}",2

echo "month 4,6,8,10,12"
./irsim ./../test/test_3_r02.ir.test -i "${1}",4,"${1}",6,"${1}",8,"${1}",10,"${1}",12

echo "month 1,3,5,7,9,11"
./irsim ./../test/test_3_r02.ir.test -i "${1}",1,"${1}",3,"${1}",5,"${1}",7,"${1}",9,"${1}",11
