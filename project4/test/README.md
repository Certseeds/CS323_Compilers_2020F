<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-29 20:20:35
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-30 16:04:08
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# Introduce

In the begining, the folder have

``` tree
.
├── test_4_r01.ir
├── test_4_r01.spl
├── test_4_r02.ir
├── test_4_r02.spl
├── test_4_r03.ir
├── test_4_r03.spl
```

and now it is

``` tree
.
├── CMakeLists.txt
├── README.md
├── read_and_write.hpp
├── test.tree
├── test_4_r01.asm
├── test_4_r01.cpp
├── test_4_r01.ir
├── test_4_r01.test.asm
├── test_4_r01.test.ir
├── test_4_r01.spl
├── test_4_r02.asm
├── test_4_r02.cpp
├── test_4_r02.ir
├── test_4_r02.test.asm
├── test_4_r02.test.ir
├── test_4_r02.spl
├── test_4_r03.asm
├── test_4_r03.cpp
├── test_4_r03.ir
├── test_4_r03.test.asm
├── test_4_r03.test.ir
├── test_4_r03.spl
```

`*.ir` come from `*.spl` file by default.
`*.test.ir` come from `*.spl` file by my compiler.
`*.cpp` is `*.spl`'s translation in cpp.
`*.asm` translate `*.spl` to mips32 Assembly by handwrite.
`*.test.asm` translate `*.spl` to mips32 Assembly by my compiler.
