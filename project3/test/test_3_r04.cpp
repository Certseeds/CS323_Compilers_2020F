#include "read_and_write.hpp"

int sqr(int i1) {
    return i1 * i1;
}

int cbc(int i2) {
    return i2 * i2 * i2;
}

int main() {
    int a, r;
    a = read();
    write(a);
    r = sqr(a);
    write(r);
    r = cbc(r);
    write(r);
    return 0;
}
