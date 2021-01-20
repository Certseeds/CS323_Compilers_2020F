/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 14:41:30
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-20 14:49:19
 */

#ifndef CS323_COMPILERS_PROJECT4_TEST_READ_AND_WRITE_HPP
#define CS323_COMPILERS_PROJECT4_TEST_READ_AND_WRITE_HPP

#include <cstdint>
#include <iostream>

int32_t read() {
    int32_t readed = 0;
    std::cin >> readed;
    return readed;
}

int32_t write(int32_t write_num) {
    std::cout << write_num << std::endl;
}

#endif  //CS323_COMPILERS_PROJECT4_TEST_READ_AND_WRITE_HPP
