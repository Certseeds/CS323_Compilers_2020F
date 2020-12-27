#include "read_and_write.hpp"

int main() {
    int month, year;
    year = read();
    month = read();
    if (year == (year / 100 * 100)) {
        if (year == (year / 400 * 400)) {
            if (month == 2) {
                write(29);// 2000,{2}
            } else if (month == (month / 2 * 2)) {
                write(30);// 2000,{4,6,8,10,12}
            } else
                write(31);//2000,{1,3,5,7,9,11}
        } else {
            if (month == 2) {
                write(28);// 1900,{2}
            } else if (month == (month / 2 * 2)) {
                write(30);//1900,{4,6,8,10,12}
            } else {
                write(31);//1900,{1,3,5,7,9,11}
            }
        }
    } else if (year == (year / 4 * 4)) {
        if (month == 2) {
            write(29);//1984,{2}
        } else if (month == (month / 2 * 2)) {
            write(30);//1984,{4,6,8,10,12}
        } else {
            write(31);//1984,{1,3,5,7,9,11}
        }
    } else {
        if (month == 2) {
            write(28);//1919,{2}
        } else if (month == (month / 2 * 2)) {
            write(30);//1919,{4,6,8,10,12}
        } else {
            write(31);//1919,{1,3,5,7,9,11}
        }
    }
    return 0;
}
