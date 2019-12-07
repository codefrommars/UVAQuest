#include <iostream>

unsigned int modFuel( int mass ) {
    int required = std::floor(mass / 3) - 2;
    
    if( required < 0 )
        return 0;

    return required + modFuel(required);
}

int main() {
    int mass;
    unsigned int fuel = 0;

    while( std::cin >> mass )
        fuel += modFuel(mass);

    std::cout << fuel << std::endl;

    //std::cout << modFuel(100756) << std::endl;

    return 0;
}