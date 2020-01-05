#include <iostream>
#include <ostream>
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

// bool isValidState(int k, KeySet keys, KeySet* kDep){
//     //std::cout << kDep[k] << std::endl;
//     for( int i = 0 ; i < keys.size(); i++) {

//         if( !keys.test(i) )
//             continue;

//         //i is in the keysset
//         if( kDep[i].test(k) )
//             return false;
//     }
//     return true;
// }

// bool nextValidState(int k, int* st, KeySet* keys, KeySet* kDep){
//     for( int j0 = st[0]; j0 < keys[0].size(); j0++ ){
//         if( !keys[0].test(j0) )
//             continue;

//         if(!isValidState(j0, keys[r0], kDep) ){
//             continue;
//         }

//         for( int j1 = st[1]; j1 < keys[1].size(); j1++ ){
//             if( !keys[1].test(j1) )
//                 continue;

//             if(!isValidState(j1, keys[1], kDep) ){
//                 continue;
//             }

//             for( int j2 = st[2]; j2 < keys[2].size(); j2++ ){
//                 if( !keys[2].test(j2) )
//                     continue;

//                 if(!isValidState(j2, keys[2], kDep) ){
//                     continue;
//                 }

//                 for( int j3 = st[3]; j3 < keys[3].size(); j3++ ){
//                     if( !keys[3].test(j3) )
//                         continue;

//                     if(!isValidState(j3, keys[3], kDep) ){
//                         continue;
//                     }
//                     //This one is valid.
//                     st[0] = j0;
//                     st[1] = j1;
//                     st[2] = j2;
//                     st[3] = j3;
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }

int encode(int* k){
    return KEYS_LEN * ( KEYS_LEN * (KEYS_LEN * k[0] + k[1]) * k[2] ) + k[3]; 
}
struct State { 
    //KeySet keys;
    KeySet keys[4];
    int r[4];

    bool operator == (const State &o) const {
        // std::cout << "Checking ==  " << std::endl;
        for(int i = 0; i < 4; i++){
            if( keys[i].to_ulong() != o.keys[i].to_ulong() )
                return false;
            if( r[i] != o.r[i] )
                return false;
        }
        return true;
        //return keys.to_ulong() == o.keys.to_ulong() && 
        // return keys == o.keys && 
        //         r[0] == o.r[0] &&
        //         r[1] == o.r[1] &&
        //         r[2] == o.r[2] &&
        //         r[3] == o.r[3];
    }

    bool operator < (const State &o) const{
        // std::cout << "Checking < " << std::endl;
        // if( keys.to_ulong() < o.keys.to_ulong())
        for(int i = 0; i < 4; i++){
            if( keys[i].to_ulong() < o.keys[i].to_ulong() )
                return true;

            if( o.keys[i].to_ulong() < keys[i].to_ulong() )
                return false;
        }

        for(int i = 0; i < 4; i++){
            if( r[i] < o.r[i] )
                return true;
            if( o.r[i] < r[i] )
                return false;
        }
        //They are equal
        return false;
    }

friend std::ostream& operator <<(std::ostream& out, const State& state){
        for( int r = 0; r < 4; r++)
            out << (char)(state.r[r] + 'a');
        out << "{";
        for( int r = 0; r < 4; r++)
            for( int i = 0; i < KEYS_LEN; i++){
                if( state.keys[r].test(i) )
                    out << (char)(i + 'a') << "";
            }  
        out << "}";
        return out; 
    }
};

bool isValidPartialState(int k, KeySet &keys, KeySet* kDep){
    if( keys.count() == 0 )
        return kDep[k].count() == 0;
    
    for( int i = 0 ; i < keys.size(); i++) {
        if( !keys.test(i) )
            continue;

        //i is in the keysset
        if( kDep[i].test(k) )
            return false;

    }    
    return true;
}

bool isValidState(State *state, KeySet* kDep){
//  std::cout << keys << std::endl;
    unsigned long mask = 0;
    for( int r = 0; r < 4; r++ ){
        mask |= state->keys[r].to_ulong();
    }

    KeySet inv(mask);

    for( int r = 0; r < 4; r++ ){
        if( !state->keys[r].any() )
            continue;
        int sR = state->r[r];
        for( int i = 0; i < kDep[sR].size(); i++ ){
            if( !kDep[sR].test(i) )
                continue;
            if( !inv.test(i) )
                return false;
        }
        // int k = state->r[r];
        // //std::cout << kDep[k] << std::endl;
        // //KeySet keys(state->keys[i]);
        // for( int i = 0 ; i < state->keys[r].size(); i++) {

        //     if( !state->keys[r].test(i) )
        //         continue;

        //     //i is in the keysset
        //     if( kDep[i].test(k) )
        //         return false;
        // }
        // if( !isValidPartialState(state->r[r], state->keys[r], kDep) )
        //     return false;
    }
    return true;
}

bool isValidFinalState(State *state, KeySet* kDep){
//  std::cout << keys << std::endl;
    for( int r = 0; r < 4; r++ ){
        // int k = state->r[r];
        // //std::cout << kDep[k] << std::endl;
        // //KeySet keys(state->keys[i]);
        // for( int i = 0 ; i < state->keys[r].size(); i++) {

        //     if( !state->keys[r].test(i) )
        //         continue;

        //     //i is in the keysset
        //     if( kDep[i].test(k) )
        //         return false;
        // }
        if( !isValidPartialState(state->r[r], state->keys[r], kDep) )
            return false;
    }
    return true;
}

void toState(int* robots, KeySet* keys, State *state){
    //state->keys = 0;
    for(int i = 0; i < 4; i++){
        state->r[i] = robots[i];
        state->keys[i] = keys[i].to_ulong();
    }
}

// /Not listing correctly the final states !!!
// The + 1 in the cycle is not correct.

// Include the minCost function in the s == -1

bool isEmpty(const State* st, int** dist){
    for(int r = 0; r < 4; r++)
        if( st->keys[r].count() != 0 )
            return false;
    
    return true;
}

int isFinalState(const State* st, int** dist){
    int cost = 0;
    for(int r = 0; r < 4; r++){
        //KeySet ks(st->keys[r]);

        if( st->keys[r].count() != 1 )
            return -1;

        for( int j = 0; j < st->keys[r].size(); j++ ){
            if( st->keys[r].test(j) ){
                cost += dist[j][j];
                break;
            }                
        }
    }
    return cost;
    // for(int r = 0; r < 4; r++){
    //     //KeySet ks(st->keys[r]);

    //     if( st->keys[r].count() != 0 )
    //         return false;
    // }
    // return true;

}


int getCost(State* state, KeySet* kDep, int** dist, std::map< State, int > &mem){

    // std::cout << "cost: " << *state ;
    if( !isValidState(state, kDep) ){
        // std::cout << " Not valid" << std::endl;
        
        return 1000000;
    }
    // std::cout << " valid" << std::endl;

    // std::cout << "Finding: ";
    // for(int i = 0; i < 4; i++){
    //     std::cout << (char)(state->r[i] + 'a') << " (" << state->keys[i] << ") ";
    // }
    // std::cout << std::endl;
    // if( isValidState(state, kDep) ){
    //     std::cout << "Valid" << std::endl;
    // }
    // State st;
    // //int k = encode(robots);
    // toState(robots, keys, &st);

    // std::cout << "Is it memoized? " << std::endl;
    if( mem.count( *state ) == 1 ){
        //  std::cout << "Yes " << std::endl;
        return mem[*state];
    }
    // std::cout << "No " << std::endl;
    //Check if it's a final state
    if( isEmpty(state, dist) ){
        mem[*state] = 0;
        // std::cout << "Empty state" << std::endl;
        // std::cout << "Final State, cost: " << 0 << std::endl;
        return 0;
    }
    // int cost = isFinalState(state, dist);
    // if( cost >= 0 ){
    //     // std::cout << "Final State, cost: " << cost << std::endl;
    //     mem[*state] = cost;
    //     return cost;
    // }

    int cost = 0;

    int min = 1000000;
    for(int r = 0; r < 4; r++){
        
        if( state->keys[r].count() == 0 ){
            // std::cout << r << " is empty" << std::endl;
            continue;
        }
        // KeySet keys(st.keys[r]);
        // int k = st.r[r];
        // keys.reset(k);
        // st.keys[r] = keys.to_ulong();

        int k = state->r[r];
        state->keys[r].reset(k);
        // std::cout << r << " leaving " << (char)(k + 'a') << std::endl;
        if( state->keys[r].count() == 0 ){
            // std::cout << r << " empty: " << *state << " valid: " << isValidState(state, kDep) << std::endl;
            if(isValidState(state, kDep) ){
                cost = getCost(state, kDep, dist, mem) + dist[k][k];
                if( cost < min )
                    min = cost;
            }               
        }else{
            //std::cout << "Checking " << r << " in " << (char)(k + 'a') << std::endl;
            //std::cout << "Jump " << r << " to " << (char)(j + 'a') << std::endl;
            for( int j = 0; j < state->keys[r].size(); j++ ){
                if( !state->keys[r].test(j) )
                    continue;
                // std::cout << "Jump " << r << " to " << (char)(j + 'a') << std::endl;
                state->r[r] = j;

                if(!isValidState(state, kDep) )
                    continue;
                
                //std::cout << "is valid" << std::endl;
                
                cost = getCost(state, kDep, dist, mem) + dist[j][k];
                if( cost < min )
                    min = cost;
                // std::cout << "Updated min: " << min << " Keys size: " << state->keys[r].size() << std::endl;
                // state->r[r] = k;
            }
            // std::cout << "Completed " << r << " in " << (char)(k + 'a') << std::endl;
        }
        state->r[r] = k;
        state->keys[r].set(k);
    }

    mem[*state] = min;
    // unsigned long total = 0;
    // for(int i = 0; i < 4; i++){
    //     std::cout << (char)(state->r[i] + 'a') << " ";
    //     total |= state->keys[i].to_ulong();
    // }
    
    // std::cout << KeySet(total) << ": " << min << std::endl;

    return min;
}

// int getMinCost(State* state, KeySet* kDep, int** dist, std::map< State, int > &mem){

//     //State tmp;
//     int min = 1000000;
//     while( nextFinalState(4-1, state, kDep ) ){

//         int cost = getCost(state, kDep, dist, mem);
//         std::cout << "Cost of final: " << cost << std::endl;
//         if( cost < min )
//             min = cost;
//     }
//     //}

//     return min;
// }

int minFinalState(int s, State* state, KeySet* kDep, int** dist, std::map< State, int > &mem){
    // std::cout << "Calling with " << s << " : ";//<< std::endl;
    // for( int i = 0; i < 4; i++){
    //     std::cout << st[i] << " ";
    // }
    // std::cout << std::endl;
    // State tmp;
    // toState(st, keys, &tmp);


    // if( !isValidPartialState(i, state->keys[s], kDep) )
    //     continue;
    

    if( s == -1 ){

        // std::cout << "Looking into " << *state << std::endl;

        // std::cout << "End State: ";//<< std::endl;
        // for( int i = 0; i < 4; i++){
        //     std::cout << (char)(state->r[i] + 'a') << " ";
        // }

        //std::cout << " -> " << isValidState(state, kDep) << std::endl;
        
        std::cout << "Evaluating: " << *state << std::endl;
        int c = getCost(state, kDep, dist, mem);
        // std::cout << "= " << c;
        // std::cout << std::endl;
        return c;
        //Call the calc of the min cost !
        //return true;
       // return isValidState(&tmp, kDep);
    }

    //state s;
    int min = 1000000;

    for( int i = state->r[s]; i < KEYS_LEN; i++){
        if( !state->keys[s].test(i) )
            continue;
        // std::cout << "Robot " << s << " : " << (char)(i + 'a') ;
        
        if( !isValidPartialState(i, state->keys[s], kDep) ){
            // std::cout << " NOT valid." << std::endl ;
            continue;
        }

        // std::cout << " is valid." << std::endl;

        int p = state->r[s];
        state->r[s] = i;
        // std::cout << s << " has " << (char)(i + 'a') << std::endl;
        // if( nextFinalState(s - 1, first, state, kDep ) )
        //     return true;
        
        int cost = minFinalState(s - 1, state, kDep, dist, mem);
        if( cost < min )
            min = cost;

        state->r[s] = p;
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

    std::vector<Coord> robots;
    //int x, y;

    int h = 0;
    int w = 0;

    while( std::getline(std::cin, line) ){
        w = line.size();        
        for( int i = 0; i < line.size(); i++ ){
            if( line[i] == '@' ){
                Coord c;
                c.x = i;
                c.y = h;
                robots.push_back(c);
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
    for( int i = 0; i < robots.size(); i++ )
        buildKeyDeps(visited, input, robots[i].x, robots[i].y, KeySet(),kCount, kDep, -1 );
    
    std::cout << "kDep" << std::endl;
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

    //Build distances
    std::cout << "Building dist" << std::endl;
    for (auto a = keys.begin(); a != keys.end(); ++a){
        int iA = a->first - 'a';
        std::cout  << "Computing " << a->first << std::endl;
        computeDist(visited, input, a->second.x, a->second.y, dist[iA], 0, -1);
    }

    //To robots
    int originDist[KEYS_LEN];
    KeySet* access = new KeySet[robots.size()];

    for( int r = 0; r < robots.size(); r++){
        access[r].reset();
        for( int i = 0; i < KEYS_LEN; i++)
            originDist[i] = -1;

        std::cout  << "Computing @" <<r << ": ";
        computeDist(visited, input, robots[r].x, robots[r].y, &originDist[0], 0, -1);        

        for( int i = 0; i < KEYS_LEN; i++)
            if( originDist[i] != -1 ) {
                std::cout  << (char)(i + 'a') << " ";
                dist[i][i] = originDist[i];
                access[r].set(i);
            }
        std::cout << access[r] << std::endl;

    }

    for( int j = 0; j < keys.size(); j++){
        for( int i = 0; i < keys.size(); i++)
            std::cout << dist[j][i] << " ";
        std::cout << std::endl;
    }

    //std::map< unsigned long, int > * mem = new std::map< unsigned long, int >[KEYS_LEN*KEYS_LEN*KEYS_LEN*KEYS_LEN];
    std::map< State, int > mem;
    
    // for( int r = 0; r < robots.size(); r++)
    //     mem[r] = new std::map< unsigned long, int >[KEYS_LEN];
    
    State state;
    //int* st = new int[4];
    for(int i = 0; i < 4; i++){
        state.r[i] = 0;
        state.keys[i] = KeySet(access[i]);
    }

    int min = minFinalState(4-1, &state, kDep, dist, mem);
    std::cout << "Min: " << min << std::endl;
    // while( nextFinalState(4-1, &state, kDep ) ){

    //     for(int i = 0; i < 4; i++){
    //         std::cout << (char)(state.r[i] + 'a') << " ";
    //     }
    //     std::cout << isValidState(&state, kDep) ;
    //     std::cout << std::endl;
    // }
    // int min = getMinCost(&state, kDep, dist, mem);	
    // std::cout << "Min: " << min << std::endl;

    // for( int i = 0; i < keys.size(); i++ )
    //     std::cout << "Deps " << (char)(i + 'a') << ": " << kDep[i] << std::endl;

    // State tmp;
    // while( nextFinalState(4-1, st, access, kDep ) ){
    //     toState(st, access, &tmp);
        

    //     std::cout << "Found: " ; 
    //     for(int i = 0; i < 4; i++){
    //         std::cout << (char)(st[i] + 'a') << " ";
    //     }
    //     std::cout << isValidState(&tmp, kDep) ;
    //     std::cout << std::endl;
    // }
    //std::cout << nextFinalState(4-1, st, access, kDep ) << " : ";


    

    // KeySet k;
    // for(int i = 0; i < keys.size(); i++)
    //     k.set(i);
    // // for(int i = 0; i < keys.size(); i++){
    // //     std::cout << isValidState(i, k, kDep) << std::endl;
    // // }

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

    
    //std::cout << countDeps( deps, 'p' ) << std::endl;

    // for(int i = 0; i < keys.size(); i++){
    //     for(int j = 0; j < keys.size(); j++){
    //         std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::map< unsigned long, int > * mem = new std::map< unsigned long, int >[KEYS_LEN];

    // KeySet k;
    // for(int i = 0; i < keys.size(); i++)
    //     k.set(i);
    // // for(int i = 0; i < keys.size(); i++){
    // //     std::cout << isValidState(i, k, kDep) << std::endl;
    // // }
   

    // int min = getMinCost(k, kDep, dist, mem);	
    // std::cout << "Min: " << min << std::endl;
    
    
    
    
    
    // for(int i = 0; i < MAX_LEN; i++){
    //     if( deps[i] != -1 ){
    //         std::cout << (char) (i + 'A') << " -> " << (char) (deps[i] + 'A') << std::endl;
    //     }
    // }

    
    
    return 0;
}
