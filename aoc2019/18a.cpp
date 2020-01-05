#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <queue>


#define MAX_LEN ('z' - 'A' + 1)
#define ORIGIN ('z' - 'a' + 1)
#define KEYS_LEN ('z' - 'a' + 2) // @ -> 0

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

// struct Path{
//     int dst;
//     unsigned long keys;
// };



// void explore(int** visited, std::vector< std::string > map, std::queue<unsigned long> &paths, int src, int x, int y, int dst, KeySet cDep, int bd){
//     if( visited[y][x] == 1 )
//         return;
    
//     visited[y][x] = 1;

    

//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];        

//         if( map[ny][nx] == '#' )
//             continue;
        
//         if( map[ny][nx] >= 'A' && map[ny][nx] <= 'Z' ){
//             int index = map[ny][nx] - 'A';
//             cDep.set(index);
//             // //std::cout << "Adding key: " << index ;
//             // kCount[index]++;
//             // //std::cout << " was OK " << std::endl;
//             explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);
//             // kCount[index]--;
//             // if( kCount[index] == 0 )
//             cDep.reset(index);
//             continue;
//         }

//         bool isGoal = map[ny][nx] == '@' || (map[ny][nx] >= 'a' && map[ny][nx] <= 'z');

//         if( isGoal ){
//             int index = map[ny][nx] - 'a';

//             if( map[ny][nx] == '@' )
//                 index = ORIGIN;

//             if( index == src )
//                 continue;

//             std::cout<< "Found: " << (char)(index + 'a') << std::endl;

//             paths.push(index);
//             paths.push(nx);
//             paths.push(ny);
//             paths.push(cDep.to_ulong());
//             paths.push(dst);

//             // if( index != ORIGIN )
//             //     cDep.set(index);

//             // explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);
//             // if( index != ORIGIN )
//             //     cDep.reset(index);

//             // if( paths[index].count(cDep) == 1 ){
//             //     if( paths[index][cDep.to_ulong()] >= dst ){
//             //         continue;
//             //     }
//             // }

//             // paths[index][cDep.to_ulong()] = dst;

//             // std::cout << "Setting: " << (char)(index + 'a');
//             // kDeps[index] = cDep;
//             // std::cout << " was OK " << std::endl;
//             // std::cout << "Way to " << (char)( index + 'a' ) << " : " << cDep << std::endl;
//             // cDep.set(index);
//             // kCount[index]++;
//             // buildKeyDeps(visited, map, nx, ny, cDep,kCount, kDeps, BACK[dir]);
//             // kCount[index]--;
//             // if( kCount[index] == 0 )
//             //     cDep.reset(index);//Remove the dependency
//             // //std::cout << "Dep [" << (char)(index + 'A') << "] = " << " = " << (char) ( deps[index] + 'A') << std::endl;
//             continue;
//         }
//         explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);
//     }

//     visited[y][x] = 0;
// }

// void buildMatrix(bool* keysVisited, int** visited, std::vector< std::string > map, std::map<unsigned long, int>** matrix, int src, int x, int y){
//     // bool keysVisited[KEYS_LEN] = { false };
//     if( keysVisited[src] )
//         return;
   
//     std::cout<< "Testing: " << (char)(src + 'a') << std::endl;
//     std::queue<unsigned long> q;
//     //for(int dir = 0; dir < 4; dir++){
//     explore(visited, map, q, src, x, y, 0, KeySet(), -1);
//     //}
//     std::cout<< "Recovered: " << (q.size() / 5) << std::endl;

//     keysVisited[src] = true;

//     while ( q.size() > 0 ){
//         int tgt = q.front(); q.pop();
//         int nx = q.front(); q.pop();
//         int ny = q.front(); q.pop();
//         int cDepMask = q.front(); q.pop();
//         int dst = q.front(); q.pop();
        
//         if( matrix[src][tgt].count(cDepMask) == 1 ){
//             if( matrix[src][tgt][cDepMask] >= dst ){
//                 continue;
//             }
//         }

//         matrix[src][tgt][cDepMask] = dst;
        
//         if( tgt == ORIGIN )
//             continue;

//         buildMatrix(keysVisited, visited, map, matrix, tgt, nx, ny);
//     }

//     // std::queue<unsigned long> q;
//     // q.push(src);
//     // q.push(x);
//     // q.push(y);
//     // q.push(0);
//     // q.push(0);

//     // while( q.size() > 0 ){
//     //     int src = q.front(); q.pop();
//     //     int sx = q.front(); q.pop();
//     //     int sy = q.front(); q.pop();
//     //     int keys = q.front(); q.pop();
//     //     int dst = q.front(); q.pop();

//     //     for(int dir = 0; dir < 4; dir++){
//     //         explore(visited, map, q, int src, int x, int y, int dst, KeySet cDep, int bd
//     //     }
//     // }

// }
void explore(int** visited, std::vector< std::string > map, std::queue<unsigned long> &paths, int src, int x, int y, int dst, KeySet cDep, int bd){
    if( visited[y][x] == 1 )
        return;
    
    visited[y][x] = 1;

    

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
            // //std::cout << "Adding key: " << index ;
            // kCount[index]++;
            // //std::cout << " was OK " << std::endl;
            explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);
            // kCount[index]--;
            // if( kCount[index] == 0 )
            cDep.reset(index);
            continue;
        }

        bool isGoal = map[ny][nx] == '@' || (map[ny][nx] >= 'a' && map[ny][nx] <= 'z');

        if( isGoal ){
            int index = map[ny][nx] - 'a';

            if( map[ny][nx] == '@' )
                index = ORIGIN;

            if( index == src )
                continue;

            //std::cout<< "Found: " << (char)(index + 'a') << std::endl;

            paths.push(index);
            paths.push(nx);
            paths.push(ny);
            paths.push(cDep.to_ulong());
            paths.push(dst);

            if( index != ORIGIN )
                cDep.set(index);

            explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);

            if( index != ORIGIN )
                cDep.reset(index);
            continue;
        }
        explore(visited, map, paths, src, nx, ny, dst + 1, cDep, BACK[dir]);
    }

    visited[y][x] = 0;
}

void buildMatrix(bool* keysVisited, int** visited, std::vector< std::string > map, std::map<unsigned long, int>** matrix, int src, int x, int y){
    // bool keysVisited[KEYS_LEN] = { false };
    // if( keysVisited[src] )
    //     return;
   
    //std::cout<< "Testing: " << (char)(src + 'a') << std::endl;
    std::queue<unsigned long> q;
    //for(int dir = 0; dir < 4; dir++){
    explore(visited, map, q, src, x, y, 0, KeySet(), -1);
    //}
    //std::cout<< "Recovered: " << (q.size() / 5) << std::endl;

    // keysVisited[src] = true;

    while ( q.size() > 0 ){
        int tgt = q.front(); q.pop();
        int nx = q.front(); q.pop();
        int ny = q.front(); q.pop();
        int cDepMask = q.front(); q.pop();
        int dst = q.front(); q.pop();
        
        if( matrix[src][tgt].count(cDepMask) == 1 ){
            if( matrix[src][tgt][cDepMask] >= dst ){
                continue;
            }
        }

        matrix[src][tgt][cDepMask] = dst;
        
        // if( tgt == ORIGIN )
        //     continue;

        // buildMatrix(keysVisited, visited, map, matrix, tgt, nx, ny);
    }

}
// void pushEvents(std::deque<int> &pos, std::vector< std::string > map, int x, int y, int bd){
//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];

//         if( map[ny][nx] == '#' )
//             continue;
        
//         if( (map[ny][nx] >= 'A' && map[ny][nx] <= 'Z') || (map[ny][nx] >= 'a' && map[ny][nx] <= 'z')){
//             pos.push_back(nx);
//             pos.push_back(ny);
//             continue;
//         }

//         pushEvents(map, nx, ny, cDep, kDeps, BACK[dir]);
//     }
// }
// void buildKeyDeps(std::vector< std::string > map, int x, int y, KeySet cDep, KeySet* kDeps){
//     std::deque<int> pos;

//     pos.push_back(x);
//     pos.push_back(y);
//     pos.push_back(-1);
//     while( pos.size() > 0 ){

//         for( int dir = 0; dir < 4; dir++ ){
//             pushEvents()
//         }
//     }
// }
void buildKeyDeps(int** visited, std::vector< std::string > map, int x, int y, KeySet cDep, int* kCount, KeySet* kDeps, int bd){
    // std::cout << " Visited: " << visited[y][x] << std::endl ;
    if( visited[y][x] == 1 )
        return;
    
    visited[y][x] = 1;

    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        

        if( map[ny][nx] == '#' )
            continue;
        
        if( map[ny][nx] >= 'A' && map[ny][nx] <= 'Z' ){
            int index = map[ny][nx] - 'A';
            //std::cout << "Adding key: " << index ;
            cDep.set(index);
            kCount[index]++;
            //std::cout << " was OK " << std::endl;
            buildKeyDeps(visited, map, nx, ny, cDep, kCount, kDeps, BACK[dir]);
            kCount[index]--;
            if( kCount[index] == 0 )
                cDep.reset(index);//Remove the dependency
            continue;
        }

        if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
            int index = map[ny][nx] - 'a';
            // std::cout << "Setting: " << (char)(index + 'a');
            kDeps[index] = cDep;
            // std::cout << " was OK " << std::endl;
            // std::cout << "Way to " << (char)( index + 'a' ) << " : " << cDep << std::endl;
            cDep.set(index);
            kCount[index]++;
            buildKeyDeps(visited, map, nx, ny, cDep,kCount, kDeps, BACK[dir]);
            kCount[index]--;
            if( kCount[index] == 0 )
                cDep.reset(index);//Remove the dependency
            continue;
            //std::cout << "Dep [" << (char)(index + 'A') << "] = " << " = " << (char) ( deps[index] + 'A') << std::endl;
        }

        buildKeyDeps(visited, map, nx, ny, cDep, kCount,kDeps, BACK[dir]);
    }

    visited[y][x] = 0;
}

// int computeDist(int** visited, std::vector< std::string > map, int x, int y, char target, int dst, int bd){

//     if( map[y][x] == target )
//         return dst;

//     int min = 9999999;

//     if( visited[y][x] == 1 )
//         return min;
    
//     visited[y][x] = 1;


//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];

//         if( map[ny][nx] == '#' )
//             continue;

//         int cDist = computeDist(visited,map, nx, ny, target, dst + 1, BACK[dir]);
//         if( cDist < min)
//             min = cDist;
//     }

//     visited[y][x] = 0;

//     return min;
// }

// void buildDist(int** visited, std::vector< std::string > map, int ox, int oy, std::map< char, Coord > keys, int** dist){
//     //std::cout << "Building dist" << std::endl;
//     for (auto a = keys.begin(); a != keys.end(); ++a){
//         for (auto b = keys.begin(); b != keys.end(); ++b){
//             //std::cout << a->first << " vs " << b->first << std::endl;
//             int iA = a->first - 'a';
//             int iB = b->first - 'a';
           
//             if( dist[iA][iB] != -1 )
//                 continue;

//             if( iA == iB ){
//                 std::cout  << "Computing @->" << a->first << std::endl;
//                 dist[iA][iA] = computeDist(visited,map, ox, oy, a->first, 0, -1);
//                 //std::cout << "From o to " << a->first << ": " << dist[iA][iA] << std::endl;
//                 continue;
//             }

//             std::cout  << "Computing " << a->first <<" -> " << b->first << std::endl;
            
//             //std::cout << "CompDist " << a->second.x << ", " << a->second.y << ", " << b->first << std::endl;
//             dist[iA][iB] = computeDist(visited,map, a->second.x, a->second.y, b->first, 0, -1);
//             dist[iB][iA] = dist[iA][iB];               
//         }
//     }
//     for( int j = 0; j < KEYS_LEN; j++){
//         for( int i = 0; i < KEYS_LEN; i++)
//             std::cout << dist[j][i] << " ";
//         std::cout << std::endl;
//     }
// }
void computeDist(int** visited, std::vector< std::string > map, int x, int y, int* distRow, int dst, int bd){

    if( map[y][x] >= 'a' && map[y][x] <= 'z' ){
        int index = map[y][x] - 'a';
        // int cDist = computeDist(visited,map, nx, ny, distRow, dst + 1, BACK[dir]);
        // if( cDist < min)
        //     distRow
        //     min = cDist;
        if( (distRow[index] == -1) || ( dst < distRow[index] ) )
            distRow[index] = dst;
    }

    //int min = 9999999;

    if( visited[y][x] == 1 )
        return;
    
    visited[y][x] = 1;


    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( map[ny][nx] == '#' )
            continue;

        // if( map[ny][nx] >= 'a' && map[ny][nx] <= 'z' ){
        //     int index = map[ny][nx] - 'a';
        //     // int cDist = computeDist(visited,map, nx, ny, distRow, dst + 1, BACK[dir]);
        //     // if( cDist < min)
        //     //     distRow
        //     //     min = cDist;
        //     if( (distRow[index] == -1) || ( dst < distRow[index] ) )
        //         distRow[index] = dst;
        // }
        computeDist(visited,map, nx, ny, distRow, dst + 1, BACK[dir]);
    }

    visited[y][x] = 0;

}

void buildDist(int** visited, std::vector< std::string > map, int ox, int oy, std::map< char, Coord > keys, int** dist){
    //std::cout << "Building dist" << std::endl;
    


    for (auto a = keys.begin(); a != keys.end(); ++a){
        int iA = a->first - 'a';
        std::cout  << "Computing " << a->first << std::endl;
        computeDist(visited, map, a->second.x, a->second.y, dist[iA], 0, -1);
       
        // for (auto b = keys.begin(); b != keys.end(); ++b){
        //     //std::cout << a->first << " vs " << b->first << std::endl;
        //     int iA = a->first - 'a';
        //     int iB = b->first - 'a';
           
        //     if( dist[iA][iB] != -1 )
        //         continue;

        //     if( iA == iB ){
        //         // std::cout  << "Computing @->" << a->first << std::endl;
        //         // dist[iA][iA] = computeDist(visited,map, ox, oy, a->first, 0, -1);
        //         //std::cout << "From o to " << a->first << ": " << dist[iA][iA] << std::endl;
        //         continue;
        //     }

        //     std::cout  << "Computing " << a->first <<" -> " << b->first << std::endl;
            
        //     //std::cout << "CompDist " << a->second.x << ", " << a->second.y << ", " << b->first << std::endl;
        //     dist[iA][iB] = computeDist(visited,map, a->second.x, a->second.y, b->first, 0, -1);
        //     dist[iB][iA] = dist[iA][iB];               
        // }
    }

    int originDist[KEYS_LEN];
    
    for( int i = 0; i < KEYS_LEN; i++)
        originDist[i] = -1;
    std::cout  << "Computing @" << std::endl;
    computeDist(visited, map, ox, oy, &originDist[0], 0, -1);

    for( int i = 0; i < KEYS_LEN; i++)
        dist[i][i] = originDist[i];

     for( int j = 0; j < KEYS_LEN; j++){
        for( int i = 0; i < KEYS_LEN; i++)
            std::cout << dist[j][i] << " ";
        std::cout << std::endl;
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
    // std::cout << "Finding: " << k << ": " << keys << std::endl;
    if( mem[k].count(keys.to_ulong()) == 1 ){        
        return mem[k][keys.to_ulong()];
    }
    // std::cout << "Computing: " << k << ": " << keys << std::endl;

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
        //std::cout << "Invalid: " << j << ": " << keys << std::endl;
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

    int* kCount = new int[KEYS_LEN];
    int** dist = new int*[KEYS_LEN];
    for(int i = 0; i < KEYS_LEN; i++){
        kDep[i].reset();
        kCount[i] = 0;
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
    // buildDeps(input, x, y, -1, deps, -1);
    int** visited = new int*[h];
    for( int j = 0; j < h; j++){
        visited[j] = new int[w];
        for(int i = 0; i < w; i++){
            visited[j][i] = 0;
        }
    }
    // std::cout << "Building keys" << std::endl;
    //int** visited, std::vector< std::string > map, int x, int y, KeySet cDep, int* kCount, std::vector<KeySet>* kDeps, int bd
    buildKeyDeps(visited, input, x, y, KeySet(),kCount, kDep, -1 );
    // bool keysVisited[KEYS_LEN] = { false };
    // std::map<unsigned long, int>** matrix = new std::map<unsigned long, int>*[KEYS_LEN];
    // for( int i = 0; i < KEYS_LEN; i++)
    //     matrix[i] = new std::map<unsigned long, int>[KEYS_LEN];
    
    // buildMatrix(&keysVisited[0], visited, input, matrix, ORIGIN, x, y);
    
    // for( auto i = keys.begin(); i != keys.end(); ++i){
    //     //Fill for others ~!!~!!!!!
    //     char k = i->first;
    //     Coord c = i->second;
    //     buildMatrix(&keysVisited[0], visited, input, matrix, k - 'a', c.x, c.y);
    // }
    //Compute closure.



    // for( int i = 0; i < KEYS_LEN; i++){
    //     for( int j = 0; j < KEYS_LEN; j++){
    //         std::cout << matrix[i][j].size() << " ";
    //     }
    //     std::cout << std::endl;
    // }



    // for(int i = 0; i < KEYS_LEN; i++){
    //     if( !kDep[i].any() )
    //         continue;
        
    //     std::cout << (char)(i + 'a') << ": ";
    //     for(int j = 0; j < KEYS_LEN; j++){
    //         if( kDep[i].test(j) )
    //         std::cout << (char)(j + 'a') << " "; 
    //     }

    //     std::cout << std::endl;
    // } 
    std::cout << "Building dist" << std::endl;
    buildDist(visited,input, x, y, keys, dist);

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
    for(int i = 0; i < keys.size(); i++)
        k.set(i);
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
