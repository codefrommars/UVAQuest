#include <iostream>
#include <string>
#include <map>

struct Point { int x; int y; };
std::map<char, Point > dirs = {// NWSE -> deltas, LR -> rotation coord. multiplier
    {'R', {-1, 1}}, {'N', {0, 1}},  
    {'W', {-1, 0}},                 {'E', {1, 0}},
                    {'S', {0, -1}}, {'L', {1, -1}},
};

void run(Point* fwd, Point* mv, Point* tgt){//Points affected by [F], [NSWE], [LR]
    for( std::string cmd; std::cin >> cmd; ){
        char c = cmd[0];
        int p = atoi( cmd.substr(1).c_str() );
        Point d = dirs[c];

        if( c == 'L' || c == 'R' ){
            for( int deg = p; deg > 0; deg -= 90 ){
                int rx = d.x * tgt->x;
                int ry = d.y * tgt->y;
                tgt->x = ry;
                tgt->y = rx;
            }
        }else if( c == 'F' ){
            fwd->x += p * (tgt->x);
            fwd->y += p * (tgt->y);
        }else{// N S W E
            mv->x += p * d.x;
            mv->y += p * d.y;
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