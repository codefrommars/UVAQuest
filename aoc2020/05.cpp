#include <iostream>

int decode( const char* c, char cOne, int mult ){
    if( mult == 0 )
        return 0;

    int val = ( *c == cOne ) * mult; 
    return decode(c + 1, cOne, mult >> 1 ) + val;
}

int seatID(const char* line){
    int row = decode(line, 'B', 64);
    int col = decode(&line[7], 'R', 4);
    return row * 8 + col;
}

void part1() {
    char line[16];
    int maxSeat = 0;

    while( std::cin >> line ){
        int id = seatID(line);
        if( id > maxSeat )
            maxSeat = id;
    }

    std::cout << maxSeat << std::endl;
}

void part2() {
    bool seats[128*8] = {false};
    char line[16];

    while( std::cin >> line ){
        int id = seatID(line);
        seats[id] = true;
    }

    for( int i = 1; i < 1023; i++ ){
        if( seats[i - 1] && !seats[i] && seats[i + 1] ){
            std::cout << i << std::endl;
            return;
        }
    }
}

int main() {
    part2();
    return 0;
}