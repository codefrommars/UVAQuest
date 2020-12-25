#include <iostream>

auto next = [](uint64_t subject, uint64_t value){return ( value * subject ) % 20201227UL;};

void part1(){
    uint64_t cardPK = 8458505, doorPK = 16050997;

    uint64_t encKey = 1;
    for( uint64_t pk = 1; cardPK != pk; pk = next(7, pk) )
        encKey = next(doorPK, encKey);
    
    std::cout << encKey << std::endl;
}

int main(){
    part1();
}