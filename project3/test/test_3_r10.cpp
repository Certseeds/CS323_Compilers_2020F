#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n > 0) {
        std::cout << 1 << std::endl;
    } else if (n < 0) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }
    return 0;
}
