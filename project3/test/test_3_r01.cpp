#include <iostream>

int main() {
    int a, b, c;
    int final = 0;//TODO
    a = 5;
    b = a * a * (a + 2);
    std::cout << b << std::endl;
    c = b / a + 1;
    std::cout << c << std::endl;
    final = a + b - c * 3 + (b / a - 4);
    std::cout << final << std::endl;
    return 0;
}
