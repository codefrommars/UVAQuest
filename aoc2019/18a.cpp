#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>


struct Coord{
    int x, y;
};

int DIRS[4][2] = {    
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

int BACK[4] = { 1, 0, 3, 2};

struct Move{    
    int x, y, distance;
};

struct State{
    std::vector< std::string > map;    
    bool keys[26] = { false };
    int keysLeft;
};

bool hasKey(State& s, char key){
    return s.keys[ key - 'a' ];
}

bool setKey(State& s, char key, bool value){
    return s.keys[ key - 'a' ] = value;
}

bool isBlocked(State &s, int nx, int ny){
    if( s.map[ny][nx] == '#' )
        return true;
    
    if( s.map[ny][nx] >= 'A' && s.map[ny][nx] <= 'Z' )
        return !hasKey(s, s.map[ny][nx] + 32 );

    return false;
}

void addMove(std::vector<Move> &moves, int x, int y, int dst ){
    for(int i = 0; i < moves.size(); i++){
        if( moves[i].x == x && moves[i].y == y ){
            if( dst < moves[i].distance ){
                moves[i].distance = dst;                
            }
            return;
        }
    }

    Move m;
    m.x = x;
    m.y = y;
    m.distance = dst;
    moves.push_back(m);

}

// struct Path{
//     int dst;
//     std::set<char> &doors;
// }

void buildDeps(std::vector< std::string > map, int x, int y, int cDep, int* deps, int bd) {
    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( map[ny][nx] == '#' )
            continue;
        
        if( map[ny][nx] >= 'A' && map[ny][nx] <= 'Z' ){
            int index = map[ny][nx] - 'A';
            deps[index] = cDep;
            buildDeps(map, nx, ny, map[ny][nx] - 'A', deps, BACK[dir]);
            continue;
        }

        if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
            int index = map[ny][nx] - 'A';
            deps[index] = cDep;
            //std::cout << "Dep [" << (char)(index + 'A') << "] = " << " = " << (char) ( deps[index] + 'A') << std::endl;
        }

        buildDeps(map, nx, ny, cDep, deps, BACK[dir]);
    }
}

int computeDist(std::vector< std::string > map, int x, int y, char target, int dst, int bd){
    if( map[y][x] == target )
        return dst;

    int min = 9999999;

    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( map[ny][nx] == '#' )
            continue;

        int cDist = computeDist(map, nx, ny, target, dst + 1, BACK[dir]);
        if( cDist < min)
            min = cDist;
    }
    return min;
}

void buildDist(std::vector< std::string > map, std::map< char, Coord > keys, int** dist){
    //std::cout << "Building dist" << std::endl;
    for (auto a = keys.begin(); a != keys.end(); ++a){
        for (auto b = keys.begin(); b != keys.end(); ++b){
            //std::cout << a->first << " vs " << b->first << std::endl;
            if( a->first == b->first )
                continue;
            int iA = a->first - 'a';
            int iB = b->first - 'a';

            if( dist[iA][iB] != -1 )
                continue;
            //std::cout << "CompDist " << a->second.x << ", " << a->second.y << ", " << b->first << std::endl;
            dist[iA][iB] = computeDist(map, a->second.x, a->second.y, b->first, 0, -1);
            dist[iB][iA] = dist[iA][iB];               
        }
    }
}
// bool buildDeps(std::vector< std::string > map, int x, int y, int dst, int* deps, int bd) {

//     if( map[y][x] == goal ){
//         return dst;
//     }

//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];

//         if( s.map[ny][nx] >= 'a' && s.map[ny][nx] <= 'z' && !hasKey(s, s.map[ny][nx]) ){
//             addMove(moves, nx, ny, dst + 1);            
//             continue;
//         }
        
//         if( isBlocked(s, nx, ny) )
//             continue;

//         findMoves(s, moves, nx, ny, dst + 1, BACK[dir]);
//     }
// }

// int getKeys(State &s, int x, int y, int dst) {

//     if( s.keysLeft == 0 ){
//        // std::cout << "Returning: "<< dst << std::endl;
//         return dst;
//     }
    
//     //Find possibilities
//     std::vector<Move> moves;
//     findMoves(s, moves, x, y, 0, -1);

//     int min = 1000000;

//     for( int i = 0; i < moves.size(); i++ ){
//         //perform move.
//         char k = s.map[ moves[i].y ][ moves[i].x ];
//         std::cout << k << ",";
//         //std::cout << "Move: "<< moves[i].x << ", " << moves[i].y << ": " << moves[i].distance << std::endl;
//         setKey(s, k, true );
//         s.keysLeft --;

//         int cost = getKeys(s, moves[i].x, moves[i].y, moves[i].distance + dst);

//         if( cost < min )
//             min = cost;

//         setKey(s, k, false );
//         s.keysLeft ++;
//     }

//     return min;
// }

int countDeps(int* deps, char a){
    int index = a - 'A';
    int count = 0;
    while( deps[index] != -1 ){
       // std::cout << "Depends on: " << deps[index] + 'A'
        index = deps[index];
        count++;
    }

    return count;
}

#define MAX_LEN ('z' - 'A')
#define KEYS_LEN ('z' - 'a')

int main() {

    std::vector< std::string > input;
    std::map< char, Coord > keys;
    std::string line;

    int* deps = new int[ MAX_LEN];

    for(int i = 0; i < MAX_LEN; i++){
        deps[i] = -1;
    }

    int** dist = new int*[KEYS_LEN];
    for(int i = 0; i < KEYS_LEN; i++){
        dist[i] = new int[KEYS_LEN];
        for(int j = 0; j < KEYS_LEN; j++){
            if( i == j )
                dist[i][j] = 0;
            else
                dist[i][j] = -1;
        }
    }
    //int deps[ 'z' - 'A'] = { -1 };
    // std::array<int,'z' - 'A'> deps;
    // deps.fill(-1);

    int x, y;

    int h = 0;
    int w = 0;

    while( std::getline(std::cin, line) ){
        w = line.size();        
        for( int i = 0; i < line.size(); i++ ){
            if( line[i] == '@' ){
                x = i;
                y = h;
                continue;
            }

            if( line[i] >= 'a' && line[i] <= 'z' ){
                //std::cout << line[i];
                Coord c;
                c.x = i;
                c.y = h;
                keys[ line[i] ] = c;
            }
        }
        h++;
        input.push_back(line);
    }

    buildDeps(input, x, y, -1, deps, -1);
    buildDist(input, keys, dist);


    std::cout << x << ", " << y << " Keys: " << keys.size() << std::endl;

    std::cout << countDeps( deps, 'p' );

    int** plan = new int*[keys.size()];
    for(int i = 0; i < keys.size(); i++){
        plan[i] = new int[KEYS_LEN];
        for(int j = 0; j < KEYS_LEN; j++)
            plan[i][j] = -1;
    }

    for( int o = 0; o < keys.size(); o++ ) {
        for( int k = 0; k < KEYS_LEN; k++ ){
            char key = k + 'a';
            if( keys.count(key) == 0)
                continue;
            
            if( countDeps(deps, key) > o ) 
                continue;
            
            plan[o][k] = 
        }
    }

    // for(int i = 0; i < KEYS_LEN; i++){
    //     for(int j = 0; j < KEYS_LEN; j++){
    //         std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for(int i = 0; i < MAX_LEN; i++){
    //     if( (int)deps[i] != -1 ){
    //         std::cout << (char) (i + 'A') << " -> " << (char) (deps[i] + 'A') << std::endl;
    //     }
    // }


    // State s;
    // s.keysLeft = keys;
    // s.map = input;

    // int cost = getKeys(s, x, y, 0);

    // std::cout << "Cost: " <<  cost << std::endl;

    return 0;
}
