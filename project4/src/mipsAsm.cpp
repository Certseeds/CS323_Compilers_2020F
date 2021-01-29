/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 15:35:30
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-29 14:19:43
 */

#include "mipsAsm.hpp"
#include <string>
#include <iostream>

inline static const std::string data_and_text =

#include "dataAndText.asm"
        ;


void mips_asm::outputDataAndText() {
    std::cout << data_and_text;
}
