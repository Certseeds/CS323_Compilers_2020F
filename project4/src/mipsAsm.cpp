//
// Created by nanos on 2021/1/20.
//
//
#include "mipsAsm.hpp"
#include <string>
#include <iostream>

inline static const std::string data_and_text =

#include "dataAndText.asm"
        ;


void mips_asm::outputDataAndText() {
    std::cout << data_and_text;
}
