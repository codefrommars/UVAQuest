#include <iostream>
#include <string>
#include <map>
//Discrete Sin: [90, 180, 270, 360] -> (((deg)/90)%4) -> [0, 1, 2, 3] -> (i%2)*(1-2*i/2) -> [0, 1, 0, -1]
#define SIN(p) ( ( (((p)/90)%4)%2)*(1 - 2*((((p)/90)%4)/2)) )

struct Point { int x; int y; };

std::map<char, Point > dirs = { {'N', {0, 1}}, {'W', {-1, 0}}, {'S', {0, -1}}, {'E', {1, 0}} };

void run(Point* fwd, Point* mv, Point* tgt){//Points affected by [F], [NSWE], [LR]
    for( std::string cmd; std::cin >> cmd; ){
        char c = cmd[0];
        int p = atoi( cmd.substr(1).c_str() );

        if( c == 'L' || c == 'R' ){
            if( c == 'R' ) p = 360 - p;
            *tgt = { tgt->x*(SIN(p+90))- tgt->y*(SIN(p)), tgt->x*(SIN(p)) + tgt->y*(SIN(p+90)) };
        }else if( c == 'F' ){
            *fwd = { fwd->x + p * (tgt->x), fwd->y + p * (tgt->y)};
        }else{// N S W E
            *mv = { mv->x + p * dirs[c].x, mv->y + p * dirs[c].y };
        }
    }
}

void part1() {
    Point ship = {0, 0}, target = {1, 0};
    run(&ship, &ship, &target); //Ship goes forward and moves, target rotates
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
}

void part2() {
    Point ship = {0, 0}, target = {10, 1};
    run(&ship, &target, &target); //Ship goes forward, target moves and rotates
    std::cout << std::abs(ship.x) + std::abs(ship.y) << std::endl;
}

int main() {
    part2();
}