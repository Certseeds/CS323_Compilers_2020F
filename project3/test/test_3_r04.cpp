#include <iostreams>

int sqr(int i1) {
    return i1 * i1;
}

int cbc(int i2) {
    return i2 * i2 * i2;
}

int main() {
    int a, r;
    std::cin >> a;
    std::cout << a << std::endl;
    r = sqr(a);
    std::cout << r << std::endl;
    r = cbc(a);
    std::cout << r << std::endl;
    return 0;
}
