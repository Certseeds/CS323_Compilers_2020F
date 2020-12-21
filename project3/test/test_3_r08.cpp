#include <iostream>

int mod(int x, int n) {
    return x - (x / n) * n;
}

int DigitSum(int y) {
    if (y == 0) {
        return 0;
    }
    return mod(y, 10) + DigitSum(y / 10);
}

int main() {
    int num;
    std::cin >> num;
    if (num < 0) {
        std::cout << -1;
    } else {
        std::cout << DigitSum(num);
    }
    return 0;
}
