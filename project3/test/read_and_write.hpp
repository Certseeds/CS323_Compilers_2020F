//
// Created by nanos on 2020/12/22.
//

#ifndef CS323_COMPLIERS_PROJECT3_TEST_READ_AND_WRITE_HPP
#define CS323_COMPLIERS_PROJECT3_TEST_READ_AND_WRITE_HPP

#include <iostream>

int read() {
    int readed = 0;
    std::cin >> readed;
    return readed;
}

int write(int write_num) {
    std::cout << write_num << std::endl;
}

#endif //CS323_COMPLIERS_PROJECT3_TEST_READ_AND_WRITE_HPP
