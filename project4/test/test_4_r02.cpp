/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 14:42:01
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-20 14:42:50
 */
#include "read_and_write.hpp"

/** Judge sign of input number*/
int32_t main() {
    int32_t n;
    n = read();
    if (n > 0) {
        write(1);
    } else if (n < 0) {
        write(-1);
    } else {
        write(0);
    }
    return 0;
}
/**
 * Input is 1 -1 0
 * Output is 1 -1 0
 * **/