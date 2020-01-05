#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>

#define MAX_LEN ('z' - 'A')
#define KEYS_LEN ('z' - 'a')

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
            buildDeps(map, nx, ny, index, deps, BACK[dir]);
            continue;
        }

        if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
            int index = map[ny][nx] - 'A';
            deps[index] = cDep;
            buildDeps(map, nx, ny, index, deps, BACK[dir]);
            continue;

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

void buildDist(std::vector< std::string > map, int ox, int oy, std::map< char, Coord > keys, int** dist){
    //std::cout << "Building dist" << std::endl;
    for (auto a = keys.begin(); a != keys.end(); ++a){
        for (auto b = keys.begin(); b != keys.end(); ++b){
            //std::cout << a->first << " vs " << b->first << std::endl;
            int iA = a->first - 'a';
            int iB = b->first - 'a';

            if( iA == iB ){
                dist[iA][iA] = computeDist(map, ox, oy, a->first, 0, -1);
                //std::cout << "From o to " << a->first << ": " << dist[iA][iA] << std::endl;
                continue;
            }

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

// int depOf(int* deps, int key, bool door){
//     if( key >= 'a' && key <= 'b' )
// }



struct PlanNode{
    int dst;
    int prev[KEYS_LEN];
};

inline int toKey(int k){
    if( k > KEYS_LEN )
        return k - ('a' - 'A');
    
    return k;
}

bool canJump( PlanNode &pp, int k, int* deps ){
    // for(int j = 0; j < KEYS_LEN; j++)
    //     std::cout << pp.prev[j] << " ";
    // std::cout << std::endl;
    //k always a key
    char q = k + ('a' - 'A');
    //int dq = deps[q];
    // for( int i = 0; i < KEYS_LEN; i++ )
    //     std::cout << "Prev: " << plan[o-1][p].prev[i] << " ";
    //std::cout <<"q: " << (char)(q + 'A') << " -> "<< (char)(deps[q] + 'A') << std::endl;
    

    while( deps[q] != -1 ){
        // std::cout << "p: " << p;
        int t = deps[q];
        if( t > KEYS_LEN )
            t -= ('a' - 'A');
        //std::cout << "Checking " << (char)(t + 'A') << " (real: " <<(char)(deps[q] + 'A') << ") in the history" << std::endl;
        if( pp.prev[ t ] < 0 ) //doesn't satisfy a dependency, can't jump p -> k
            return false;

        q = deps[q];
    }
    return true;
}

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
            // if( i == j )
            //     dist[i][j] = 0;
            // else
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


    buildDist(input, x, y, keys, dist);

    std::cout << x << ", " << y << " Keys: " << keys.size() << std::endl;


    //std::cout << countDeps( deps, 'p' ) << std::endl;

    for(int i = 0; i < keys.size(); i++){
        for(int j = 0; j < keys.size(); j++){
            std::cout << dist[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < MAX_LEN; i++){
        if( deps[i] != -1 ){
            std::cout << (char) (i + 'A') << " -> " << (char) (deps[i] + 'A') << std::endl;
        }
    }


    PlanNode pp;
    for(int j = 0; j < KEYS_LEN; j++)
        pp.prev[j] = -1;
    int to = 'p' - 'a';
    pp.prev['c' - 'a'] = -1;
    pp.prev['h' - 'a'] = 'c' - 'a';
    pp.prev['e' - 'a'] = 'h' - 'a';
    // pp.prev['d' - 'a'] = -1;
    // pp.prev['d' - 'a'] = -1;
    // pp.prev['d' - 'a'] = -1;

    std::cout << "Query: " << canJump(pp, to, deps) << std::endl;

    // for(int i = 0; i < KEYS_LEN; i++){
    //     std::cout << deps[i] << " ";
    // }

    PlanNode** plan = new PlanNode*[keys.size()];
    for(int i = 0; i < keys.size(); i++){
        plan[i] = new PlanNode[keys.size()];        
    }

    for( int i = 0; i < keys.size(); i++ ){
        //std::cout << deps[i] << " ";
        for(int j = 0; j < keys.size(); j++)
            plan[0][i].prev[j] = -1;
        //std::cout << deps[i + 'A'] << " ";
        if( deps[i + 'a' - 'A'] == -1 ){
            plan[0][i].dst = dist[i][i];
            plan[0][i].prev[i] = 0;
        }else{
            plan[0][i].dst = 1000000;
        }

        std::cout << plan[0][i].dst << " ";
    }


    std::cout << std::endl;

    for( int o = 1; o < keys.size(); o++ ) {
        //For each rank (order)
        for( int k = 0; k < keys.size(); k++ ){
            //Find best for k in rank o
            int min = 1000000;
            int min_p = -1;
            for( int p = 0; p < keys.size(); p++){
                // Check jump from p to k
                // if( p == k ) //Don't stay in the same node
                //     continue;
                //std::cout << "Plan: " << plan[o-1][p].dst << std::endl;
                // if( plan[o-1][p].dst == -1 )
                //     continue;
                if( plan[o-1][p].prev[k] != -1 ) //Already visited k
                    continue;

                //Does it have all the dependencies?
                if( !canJump(plan[o-1][p], k, deps) )
                    continue;
                
                //Satisfy all dependencies.
                if( dist[p][k] + plan[o-1][p].dst < min){
                    min = dist[p][k] + plan[o-1][p].dst;
                    min_p = p;
                }
            }            
            if( min_p != -1 ){
                //Best for k at o is coming from min_p, at distance min
                //std::cout << "Best for (o, k) : " << o << ", " << k << " = " << min_p << " ** " << dist[min_p][k] <<std::endl;
                plan[o][k].dst = min;
                for( int i = 0; i < KEYS_LEN; i++ )
                    plan[o][k].prev[i] = plan[o - 1][min_p].prev[i];

                plan[o][k].prev[k] = o;
            }else{
                plan[o][k].dst = 1000000;
                //std::cout << "No plan for " << (char)(k + 'a') << " at  " << o << std::endl ;    
            }

            std::cout << plan[o][k].dst << " ";
        }

        std::cout << std::endl;
    }

    int last = keys.size() - 1;
    int min = 1000000;
    int m = -1;
    for( int k = 0; k < keys.size(); k++ ){
        if( plan[last][k].dst < min ){
            min = plan[last][k].dst;
            m = k;
        }
    }
    std::cout << min << std::endl;
    for(int i = 0; i < keys.size(); i++ )
        std::cout << (char)(i + 'a') << " ";
    std::cout << std::endl;
    for(int i = 0; i < keys.size(); i++ )
        std::cout << plan[last][m].prev[i] << " ";



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
