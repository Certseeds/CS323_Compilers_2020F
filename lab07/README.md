<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-27 19:11:55
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-30 22:35:07
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# Exercise: Constructing JSON object

The input is a Json Object's String

Output is a C/CPP Object that contain the type and Value of each element in This Json Object.

You should reuse the lab4 & lab6 code in lab07.

PS: But You still can use your own code in c/cpp, once your code can pass compiler and run correctly,it is ok.

## how to compiler

``` shell
make clean
make main
./Object.out ${path}
# like `./Object ./data/1.json`
```

then it will output the struct for json Object