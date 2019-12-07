#include <iostream>

int main() {
    int mass;
    unsigned int fuel = 0;

    while( std::cin >> mass )
        fuel += std::floor(mass / 3) - 2;

    std::cout << fuel << std::endl;

    return 0;
}