/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 14:41:11
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-20 14:49:29
 */
#include "read_and_write.hpp"

int32_t hanoi(int32_t n, int32_t p1, int32_t p2, int32_t p3) {
    if (n == 1) {
        write(p1 * 10000 + p3);
    } else {
        hanoi(n - 1, p1, p3, p2);
        write(p1 * 10000 + p3);
        hanoi(n - 1, p2, p1, p3);
    }
    return 0;
}

int32_t main() {
    int32_t sum = 3;
    hanoi(sum, 1, 2, 3);
    return 0;
}
/**
Input No Need
OutPut is 
10003
10002
30002
10003
20001
20003
10003
*/