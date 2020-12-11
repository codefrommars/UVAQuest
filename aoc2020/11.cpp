#include <iostream>
#include <vector>
#include <string>

using Map = std::vector<std::string>;

int occupied(const Map& map, int maxLookOut, int r, int c, int dr, int dc){
    char inDir = '.';
    while(inDir == '.' && maxLookOut > 0 ){
        r += dr; c += dc;
        if( r < 0 || r >= map.size() || c < 0 || c >= map[r].size() )
            return 0;
        
        inDir = map[r][c];
        maxLookOut--;
    }
    return ( inDir == '#' );
}

int occupiedAdj(const Map& map, int max, int r, int c){
    return  occupied(map, max, r, c, -1, -1) + occupied(map, max, r, c, -1, +0) + occupied(map, max, r, c, -1, +1)+
            occupied(map, max, r, c, +0, -1) +                                  + occupied(map, max, r, c, +0, +1)+
            occupied(map, max, r, c, +1, -1) + occupied(map, max, r, c, +1, +0) + occupied(map, max, r, c, +1, +1);
}

bool step( Map& map, int* occupied, int tolerance, int maxLookOut){
    Map prev = map;
    bool changed = false;
    *occupied = 0;
    for( int r = 0; r < prev.size(); r++){
        for(int c = 0; c < prev[r].size(); c++ ){
            if( prev[r][c] == '.')
                continue;
            int adj = occupiedAdj(prev, maxLookOut, r, c);
            if( prev[r][c] == 'L' && adj == 0 ){
                map[r][c] = '#';
                changed = true;
            }else if( prev[r][c] == '#' && adj >= tolerance ){
                map[r][c] = 'L';
                changed = true;
            }
            if( map[r][c] == '#' )
                *occupied = *occupied + 1;
        }
    }
    return changed;
}

int simulate(int tolerance, int maxLookOut){
    Map map;
    for( std::string line; std::getline(std::cin, line); )
        map.push_back(line);
    int occupied = 0;
    while( step(map, &occupied, tolerance, maxLookOut) );
    return occupied;
}

void part1() {
    std::cout << simulate(4, 1) << std::endl;
}

void part2() {
    std::cout << simulate(5, INT32_MAX) << std::endl;
}

int main() {
    part2();
}