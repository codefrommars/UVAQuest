#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>
#include <bitset>


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

typedef std::bitset<KEYS_LEN> KeySet;

void buildKeyDeps(std::vector< std::string > map, int x, int y, KeySet cDep, KeySet* kDeps, int bd){
    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( map[ny][nx] == '#' )
            continue;
        
        if( map[ny][nx] >= 'A' && map[ny][nx] <= 'Z' ){
            int index = map[ny][nx] - 'A';
            cDep.set(index);
            buildKeyDeps(map, nx, ny, cDep, kDeps, BACK[dir]);
            cDep.reset(index);//Remove the dependency
            continue;
        }

        if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
            int index = map[ny][nx] - 'a';
            kDeps[index] = cDep;
            cDep.set(index);
            buildKeyDeps(map, nx, ny, cDep, kDeps, BACK[dir]);
            cDep.reset(index);//Remove the dependency
            continue;
            //std::cout << "Dep [" << (char)(index + 'A') << "] = " << " = " << (char) ( deps[index] + 'A') << std::endl;
        }

        buildKeyDeps(map, nx, ny, cDep, kDeps, BACK[dir]);
    }
}

// void buildDeps(std::vector< std::string > map, int x, int y, int cDep, int* deps, int bd) {
//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];

//         if( map[ny][nx] == '#' )
//             continue;
        
//         if( map[ny][nx] >= 'A' && map[ny][nx] <= 'Z' ){
//             int index = map[ny][nx] - 'A';
//             deps[index] = cDep;
//             buildDeps(map, nx, ny, index, deps, BACK[dir]);
//             continue;
//         }

//         if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
//             int index = map[ny][nx] - 'A';
//             deps[index] = cDep;
//             buildDeps(map, nx, ny, index, deps, BACK[dir]);
//             continue;

//             //std::cout << "Dep [" << (char)(index + 'A') << "] = " << " = " << (char) ( deps[index] + 'A') << std::endl;
//         }

//         buildDeps(map, nx, ny, cDep, deps, BACK[dir]);
//     }
// }

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

bool isValidState(int k, KeySet keys, KeySet* kDep){
    //std::cout << kDep[k] << std::endl;
    for( int i = 0 ; i < keys.size(); i++) {

        if( !keys.test(i) )
            continue;

        //i is in the keysset
        if( kDep[i].test(k) )
            return false;
    }
    return true;
}

int getCost(int k, KeySet keys, KeySet* kDep, int** dist, std::map< unsigned long, int > * mem){
    if( mem[k].count(keys.to_ulong()) == 1 ){
        
        return mem[k][keys.to_ulong()];
    }

    if( keys.count() == 1 )
        return dist[k][k];
    
    keys.reset(k);
    int min = 1000000;
    for( int j = 0; j < keys.size(); j++ ){
        if( !keys.test(j) )
            continue;
        if(!isValidState(j, keys, kDep) ){
            //std::cout << "Invalid: " << j << ": " << keys << std::endl;
            continue;
        }

        int cost = getCost(j, keys, kDep, dist, mem) + dist[j][k];
        if( cost < min )
            min = cost;
    }
    keys.set(k);

    mem[k][keys.to_ulong()] = min;

    return min;
}

int getMinCost(KeySet keys, KeySet* kDep, int** dist, std::map< unsigned long, int > * mem){
    int min = 1000000;
    for( int j = 0; j < keys.size(); j++ ){
        if( !keys.test(j) )
            continue;

        if(!isValidState(j, keys, kDep) ){
        std::cout << "Invalid: " << j << ": " << keys << std::endl;
            continue;
        }

        int cost = getCost(j, keys, kDep, dist, mem);
        if( cost < min )
            min = cost;
    }

    return min;
}


int main() {
    std::vector< std::string > input;
    std::map< char, Coord > keys;
    std::string line;

    int* deps = new int[ MAX_LEN];
    KeySet* kDep = new KeySet[KEYS_LEN];

    for(int i = 0; i < MAX_LEN; i++){
        deps[i] = -1;
    }

    int** dist = new int*[KEYS_LEN];
    for(int i = 0; i < KEYS_LEN; i++){
        kDep[i].reset();
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

    //buildDeps(input, x, y, -1, deps, -1);
    buildKeyDeps(input, x, y, KeySet(), kDep, -1 );


    for(int i = 0; i < KEYS_LEN; i++){
        if( !kDep[i].any() )
            continue;
        
        std::cout << (char)(i + 'a') << ": ";
        for(int j = 0; j < KEYS_LEN; j++){
            if( kDep[i].test(j) )
            std::cout << (char)(j + 'a') << " "; 
        }

        std::cout << std::endl;
    } 

    buildDist(input, x, y, keys, dist);

    std::cout << x << ", " << y << " Keys: " << keys.size() << std::endl;


    //std::cout << countDeps( deps, 'p' ) << std::endl;

    // for(int i = 0; i < keys.size(); i++){
    //     for(int j = 0; j < keys.size(); j++){
    //         std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::map< unsigned long, int > * mem = new std::map< unsigned long, int >[KEYS_LEN];

    KeySet k;
    k.set();
    // for(int i = 0; i < keys.size(); i++){
    //     std::cout << isValidState(i, k, kDep) << std::endl;
    // }
   

    int min = getMinCost(k, kDep, dist, mem);	
    std::cout << "Min: " << min << std::endl;
    
    
    
    
    
    // for(int i = 0; i < MAX_LEN; i++){
    //     if( deps[i] != -1 ){
    //         std::cout << (char) (i + 'A') << " -> " << (char) (deps[i] + 'A') << std::endl;
    //     }
    // }

    
    
    return 0;
}
