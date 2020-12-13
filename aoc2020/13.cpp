#include <iostream>
#include <string>

void part1() {
    int est = 0;
    std::cin >> est;
    int prod, min = 9999999;

    for( std::string tt; std::getline(std::cin, tt, ','); ){
        if( tt[0] == 'x' )
            continue;
        int id = atoi( tt.c_str() );
        int wait = id - (est % id);
        if( wait < min ){
            min = wait;
            prod = id * wait;
        }
    }
    std::cout << prod << std::endl;
}

void part2() {
    int est = 0, mod = 0;
    int64_t t = 0, d = 1;

    std::cin >> est; //ignore

    for( std::string tt; std::getline(std::cin, tt, ','); mod++){
        if( tt[0] == 'x' )
            continue;
        
        int id = atoi( tt.c_str() );

        while( (t + mod) % id != 0 ) 
            t += d;
        d *= id;
    }
    std::cout << t << std::endl;
}

int main() {
    part2();
}