#include <iostream>
#include <algorithm>

int seatID( const char* c , int id){
    if( *c == 0 )
        return id;

    int bit = ( *c == 'B' || *c == 'R' ) ; 
    return seatID(c + 1, 2 * id + bit ) ;
}

void part1() {
    char line[16];
    int maxSeat = 0;

    while( std::cin >> line )
        maxSeat = std::max(maxSeat, seatID(line, 0) );
    
    std::cout << maxSeat << std::endl;
}

void part2() {
    bool seats[128*8] = {false};
    char line[16];

    while( std::cin >> line )
        seats[seatID(line, 0)] = true;

    for( int i = 1; i < 1023; i++ ){
        if( seats[i - 1] && !seats[i] && seats[i + 1] ){
            std::cout << i << std::endl;
            return;
        }
    }
}

int main() {
    part1();
    return 0;
}