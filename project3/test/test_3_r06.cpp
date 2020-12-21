#include <iostream>

int hanoi(int n, int p1, int p2, int p3) {
    if (n == 1) {
        std::cout << p1 * 1000000 + p3 << std::endl;
    } else {
        hanoi(n - 1, p1, p3, p2);
        std::cout << p1 * 1000000 + p3 << std::endl;
        hanoi(n - 1, p2, p1, p3);
    }
    return 0;
}

int main() {
    int sum = 3;
    hanoi(sum, 1, 2, 3);
    return 0;
}
