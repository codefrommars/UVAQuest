#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <queue>
#include <algorithm>


// #define MAX_LEN ('z' - 'A' + 1)
// #define ORIGIN ('z' - 'a' + 1)
// #define KEYS_LEN ('z' - 'a' + 2) // @ -> 0

bool insert(std::map<std::string, int> &map, std::string k, int& id){
    bool isNew = false;
    if( map.count(k) == 0 ){
        map[k] = map.size();
        isNew = true;
    }
    id = map[k];

    //std::cout<<"Found " << k << ": " << id << " (" << isNew << ")" << std::endl;

    return isNew;
}

struct Coord{
    int x, y;
};

std::vector< std::string > input;
std::vector< std::vector<Coord> > portals;
std::map<int, int> coord2Portal;

int DIRS[4][2] = {    
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

int BACK[4] = { 1, 0, 3, 2};

void computeDist(int o, bool** visited, int x, int y, int* distRow, int dst, int bd){

    // if( map[y][x] >= 'a' && map[y][x] <= 'z' ){
    //     int index = map[y][x] - 'a';
    //     if( (distRow[index] == -1) || ( dst < distRow[index] ) )
    //         distRow[index] = dst;
    // }

    int coord = 10000 * y + x;
    if( coord2Portal.count(coord) ){
        //x, y is a portal
        if( coord2Portal[coord] != o ){ //Not from where we started
            // std::cout << "Found " << coord2Portal[coord] << std::endl;
            int p = coord2Portal[coord];
            //Mark the distance
            distRow[p] = std::min(dst, distRow[p]);
            return;
        }
    }

    if( visited[y][x])
        return;
    
    visited[y][x] = true;

    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( input[ny][nx] != '.' )
            continue;

        computeDist(o, visited, nx, ny, distRow, dst + 1, BACK[dir]);
    }

    visited[y][x] = false;

}

inline bool isUpper(char a){
    return a >= 'A' && a <= 'Z';
}

// void computeDist(int o, int* distRow, bool** visited, int x, int y, int dst, int bd){
//     if( visited[y][x] )
//         return;

//     visited[y][x] = true;

//     int coord = 10000 * y + x;
//     if( coord2Portal.count(coord) ){
//         //x, y is a portal
//         if( coord2Portal[coord] != o ){ //Not from where we started
//             int p = coord2Portal[coord];
//             //Mark the distance
//             dist[o][p] = std::min(dst, dist[o][p]);
//             dist[p][o] = dist[o][p];
//         }
//     }

//     for( int dir = 0; dir < 4; dir++ ){
//         if( dir == bd )
//             continue;
                
//         int nx = x + DIRS[dir][0];
//         int ny = y + DIRS[dir][1];

//         if( input[ny][nx] == '#' )
//             continue;

//         computeDist(o, dist, visited, nx, ny, dst + 1, BACK[dir]);
//     }
// }

int main() {
    std::map<std::string, int> mapper;
    
    std::string line;

    while( std::getline(std::cin, line) ){
        input.push_back(line);
    }

    char cPortal[3] = {0};
    bool** visited = new bool*[input.size()];

    // std::vector< std::vector<int> > map;

    //Find H
    for( int j = 0; j < input.size(); j++){
        visited[j] = new bool[input[j].size()];
        // std::vector<int> row;
        int lastH = -10;
        for(int i = 0; i < input[j].size(); i++){
            visited[j][i] = false;

            if( input[j][i] == ' ' ){
                lastH = -1;
                // row.push_back(-10);
            }

            if( input[j][i] == '.' ){
                lastH = i;
                // row.push_back(-1);
            }

            if( isUpper(input[j][i]) ){
                cPortal[0] = input[j][i];
                //Portal. 2 options, it's h or v
                if( isUpper(input[j][i + 1]) ){
                    cPortal[1] = input[j][i + 1];
                    int id = 0;
                    Coord c = {lastH, j};
                    if( lastH != (i - 1) )
                        c.x = i + 2;
                    if( insert(mapper, std::string(cPortal), id) ){
                        std::vector<Coord> coords;
                        coords.push_back(c);
                        portals.push_back(coords);
                    }else
                        portals[id].push_back(c);
                    
                    coord2Portal[c.y * 10000 + c.x]= id;
                    //input[j][i + 1] = '#';
                }
            }
        }
    }
    //Find V
    for(int i = 0; i < input[0].size(); i++){
        int lastV = -10;
        for( int j = 0; j < input.size(); j++){
            if( input[j][i] == ' ' )
                lastV = -1;

            if( input[j][i] == '.' )
                lastV = j;

            if( isUpper(input[j][i]) ){
                cPortal[0] = input[j][i];
                //Portal. 2 options, it's h or v
                if( isUpper(input[j + 1][i]) ){
                    cPortal[1] = input[j + 1][i];
                    int id = 0;
                    Coord c = {i, lastV};
                    if( lastV != (j - 1) )
                        c.y = j + 2;
                    if( insert(mapper, std::string(cPortal), id) ){
                        std::vector<Coord> coords;
                        coords.push_back(c);
                        portals.push_back(coords);
                    }else
                        portals[id].push_back(c);

                    coord2Portal[c.y * 10000 + c.x]= id;
                    //input[j + 1][i] = '#';
                }
            }
        }
    }
    int N = mapper.size();

    int ** dist = new int*[N];
    for(int i = 0; i < N; i++){
        dist[i] = new int[N];
        for(int j = 0; j < N; j++){
            if( i == j )
                dist[i][j] = 0;
            else
                dist[i][j] = 1000000;
        }
    }

    // for(auto i = mapper.begin(); i != mapper.end(); ++i){
    //     Coord c0 = portals[i->second][0];
    //     Coord c1 = portals[i->second][1];

    //     std::cout << i->second << ", ";
    //     std::cout << i->first << " : " << c0.x << ", " << c0.y << " = " << coord2Portal.count(10000 * c0.y + c0.x);
        
        
    //     if( portals[i->second].size() == 2 )
    //         std::cout << " -> "  << c1.x << ", " << c1.y  << " = " << coord2Portal.count(10000 * c1.y + c1.x);
        
    //     std::cout << std::endl;
    // }

    for( int i = 0; i < portals.size(); i++) {
        // std::cout << "Building " << i << std::endl;
        for( int p = 0; p < portals[i].size(); p++){
            // std::cout << "Coord " << p << std::endl;
            computeDist(i, visited, portals[i][p].x, portals[i][p].y, dist[i], 0, -1);
        }
    }


    //Transitive closure
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                if( dist[i][k] + dist[k][j] + 1 < dist[i][j] )
                    dist[i][j] = dist[i][k] + dist[k][j] + 1;

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int aa = mapper["AA"];
    int zz = mapper["ZZ"];

    std::cout << dist[aa][zz] << std::endl;

    return 0;
}
