/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 14:43:08
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-20 14:49:38
 */
#include "read_and_write.hpp"
int32_t main() {
    int32_t a = 110;
    int32_t b = 97;
    int32_t c = 3;
    c = a - b + c * 2;
    write(c);
    return 0;
}
/**
 * Input No Need
 * Output is 19
 * **/