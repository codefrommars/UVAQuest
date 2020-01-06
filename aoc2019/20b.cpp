#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <queue>
#include <deque>
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

struct Portal{
    int code;
    int id;
    int inner;
    int x, y;
};
std::vector< std::string > input;
std::vector< Portal > portals;
std::map<int, int> coord2Portal;
std::map<int, int[2]> portalLinks; // 0: outter, 1: inner
std::map<int, std::string > names;

std::map < __int64 , int > mem ;
std::map < __int64 , bool > v ;

int DIRS[4][2] = {    
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

int BACK[4] = {1, 0, 3, 2};


int getMem(int level, int portal){
    int sgn = level > 0 ? 1 : 0;

    __int64 index = (__int64)(2 * portals.size() * std::abs(level)) + 
                    (__int64)portals.size() * sgn + portal;

    //std::cout << "getting " << portal << "(" << names[portal] << "), " << level << std::endl;

    if( mem.count(index) == 0 )
        return -1;

    return mem[index];
}
//  setMem(level[aa][i], i, full[aa][i]);
void setMem(int level, int portal, int dst){
     int sgn = level > 0 ? 1 : 0;

    __int64 index = (__int64)(2 * portals.size() * std::abs(level)) + 
                    (__int64)portals.size() * sgn + portal;
    mem[index] = dst;

    //std::cout << "setting: " << portal << ", " << level << ": " << dst << std::endl;
}

__int64 encode(int portal, int level){
    return (__int64)(portals.size() * level) + (__int64)portal;
}

// int findMin(int start, int end, int p, int lvl, int** dist, int** dLvl){
//     int s = getMem(lvl, p);
//     if( s != -1 )
//         return s;

//     int min = 1000000;

//     for(int i = 0; i < portals.size(); i++){
//         if( dist[i][p] <= 0 )
//             continue;
//         // i can go to p
//         if( i == start && lvl != 0 )
//             return 1000000;
//         if( i == end && lvl != 0 )
//             continue;
//         // if( i == )
//         //i is a portal
//         Portal iP = portals[i];
//         int dl = 1 - 2 * iP.inner;
//         int other = portalLinks[iP.code][1 - iP.inner];
//         std::cout << "From: " << names[p] << "(" << lvl << ") to " << names[other] << " at " << (lvl + dl) << std::endl;
//         int cost = findMin(start, end, other, lvl + dl, dist, dLvl) + dist[i][p];

//         if( cost < min ){
//             min = cost;
//         }
//     }
    
//     setMem(lvl, p, min);

//     return min;
// }


void computeDist(int o, bool** visited, int x, int y, int* distRow, int dst,  int bd){
    int coord = 10000 * y + x;
    if( coord2Portal.count(coord) ){
        if( coord2Portal[coord] != o ){ //Not from where we started
            int p = coord2Portal[coord];
            if( distRow[p] < 0 )
                distRow[p] = dst;
            else
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


int portalByCode(int code){
    for( int i = 0; i < portals.size(); i++){
        if( portals[i].code == code )
            return i;
    }
    return -1;
}

int search(int start, int end, int** dist){

    std::deque<int> q;

    q.push_back(start);
    q.push_back(0); //lvl
    q.push_back(0); //dst

    while( !q.empty() ){
        int p = q.front(); q.pop_front();
        int lvl = q.front(); q.pop_front();
        int dst = q.front(); q.pop_front();


        if( v.count(encode(p, lvl)) > 0 ){ //already visited
            // std::cout << "Ignoring: " << names[p] << ", " << lvl << std::endl;
            continue;
        }

        v[ encode(p,lvl) ] = true;
        // std::cout << "Visiting: " << names[p] << ", " << lvl << ": ";

        for(int i = 0; i < portals.size(); i++){
            if( dist[p][i] <= 0 )
                continue;
            
            Portal iP = portals[i];
            
            if( i == start )
                continue;

            if( i == end ){
                if( lvl != 0 )
                    continue;
                // std::cout << "Found: " << names[i] << ", " << lvl << ": " << dst + dist[p][i] << std::endl;
                return dst + dist[p][i];
            }
            
            if( lvl == 0 && !iP.inner ){
                //Anything else ignore it
                continue;
            }
            //Travel to the next
            int other = portalLinks[iP.code][1 - iP.inner];
            int dl = 2 * iP.inner - 1;
            q.push_back(other);
            q.push_back(lvl + dl);
            q.push_back(dst + dist[p][i] + 1);
            // std::cout << "Pushing: " << names[i] << "(" << (lvl + dl) << ", "<< dst + dist[p][i] + 1 << ") ";
        }
        // std::cout << std::endl;
    }

    return -1; //Not found !
}

int main() {
    std::map<std::string, int> mapper;
    
    std::string line;

    while( std::getline(std::cin, line) )
        input.push_back(line);
    
    //std::cout << input[0][16] << std::endl;

    int h = input.size();

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
            }

            if( input[j][i] == '.' ){
                lastH = i;
            }

            if( isUpper(input[j][i]) ){
                cPortal[0] = input[j][i];
                //Portal. 2 options, it's h or v
                if( isUpper(input[j][i + 1]) ){
                    cPortal[1] = input[j][i + 1];
                    Portal p;
                    insert(mapper, std::string(cPortal), p.code);

                    p.inner = !( i == 0 || i == input[j].size() - 2 );                    
                    p.x = lastH;
                    p.y = j;

                    if( lastH != (i - 1) )
                        p.x = i + 2;
                    
                    p.id = portals.size();                    
                    portals.push_back(p);                    
                    coord2Portal[p.y * 10000 + p.x] = p.id;
                    if( portalLinks.count(p.code) == 0){
                        portalLinks[p.code][0] = -1;
                        portalLinks[p.code][1] = -1;
                    }
                    portalLinks[p.code][p.inner] = p.id;
                    names[p.id] = std::string(cPortal);
                }
            }
        }
    }
     //Find V    
    for(int i = 0; i < input[0].size(); i++){        
        int lastV = -10;
        for( int j = 0; j < input.size() - 1; j++){            
            if( input[j][i] == ' ' )
                lastV = -1;

            if( input[j][i] == '.' )
                lastV = j;

            if( isUpper(input[j][i]) ){
                cPortal[0] = input[j][i];
                //Portal. 2 options, it's h or v
                if( isUpper(input[j + 1][i]) ){
                    cPortal[1] = input[j + 1][i];
                    Portal p;
                    insert(mapper, std::string(cPortal), p.code);

                    p.inner = !( j == 0 || j == input.size() - 2 );                    
                    p.x = i;
                    p.y = lastV;

                    if( lastV != (j - 1) )
                        p.y = j + 2;

                    p.id = portals.size();                    
                    portals.push_back(p);                    
                    coord2Portal[p.y * 10000 + p.x] = p.id;
                    if( portalLinks.count(p.code) == 0){
                        portalLinks[p.code][0] = -1;
                        portalLinks[p.code][1] = -1;
                    }
                    portalLinks[p.code][p.inner] = p.id;
                    names[p.id] = std::string(cPortal);
                }
            }
        }
    }

    int N = portals.size();

    int ** dist = new int*[N];
    int ** full = new int*[N];

    int ** dLvl = new int*[N];
    int ** level = new int*[N];
    for(int i = 0; i < N; i++){
        dist[i] = new int[N];
        full[i] = new int[N];
        dLvl[i] = new int[N];
        level[i] = new int[N];
        for(int j = 0; j < N; j++){
            dLvl[i][j] = 0;
            if( i == j )
                dist[i][j] = 0;
            else
                dist[i][j] = -1;
        }
    }

    //int o, bool** visited, int x, int y, int* distRow, int dst, int bd
    int* portalVisited = new int[N];
    for( int i = 0; i < N; i++){
        computeDist(i, visited, portals[i].x, portals[i].y, dist[i], 0, -1);
        portalVisited[i] = 0;
    }

    // for( int i = 0; i < N ; i++){
    //     for( int j = 0; j < N ; j++){
    //         full[i][j] = dist[i][j];
    //         level[i][j] = dLvl[i][j];
    //     }
    // }
    // for( auto link = portalLinks.begin(); link != portalLinks.end(); ++link){
    //     int id0 = link->second[0]; //outter
    //     int id1 = link->second[1]; //inner
    //     if( id0 == -1 || id1 == -1 )
    //         continue;
    //     full[id0][id1] = 1;
    //     full[id1][id0] = 1;
    //     //Outter to inner
    //     level[id0][id1] = -1;
    //     //Inner to Outter
    //     level[id1][id0] = 1;
    // }
//int* portalVisited, int p, int lvl, int tgt, int tgtLevel, int** dist, int dst

    // for(auto i = mapper.begin(); i != mapper.end(); ++i){
    //     std::cout << i->second << ": " << i->first << std::endl;
    //     // Portal pOut = portals[ portalLinks[i->second][0] ];
    //     // Portal pIn  = portals[ portalLinks[i->second][1] ];
    //     // std::cout << pOut.x << ", " << pOut.y << " => " << pIn.x << ", " << pIn.y << std::endl;
    // }
    // for( int i = 0; i < N ; i++){
    //     //std::cout << i << ": ";
    //     for( int j = 0; j < N ; j++){
    //      //   if( dist[i][j] > 0 )
    //             std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
   
    // for( int i = 0; i < N ; i++){
    //     //std::cout << i << ": ";
    //     for( int j = 0; j < N ; j++){
    //      //   if( dist[i][j] > 0 )
    //             std::cout << dLvl[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    //Transitive closure
    // for(int k = 0; k < N; k++)
    //     for(int i = 0; i < N; i++)
    //         for(int j = 0; j < N; j++){
    //             if ( full[i][k] < 0 ||  full[k][j] < 0 )
    //                 continue;

    //             if( full[i][j] < 0 ){
    //                 full[i][j] = full[i][k] + full[k][j];
    //                 level[i][j] = level[i][k] + level[k][j];
    //             }

    //             if( full[i][k] + full[k][j] < full[i][j] ){
    //                 full[i][j] = full[i][k] + full[k][j];
    //                 level[i][j] = level[i][k] + level[k][j];
    //             }
    //         }
    
    int aa = portalByCode( mapper["AA"] );
    int zz = portalByCode( mapper["ZZ"] );
    
    int min = search(aa, zz, dist);
    std::cout << min << std::endl;

    // setMem(0, aa, 0);

    // for(int i = 0; i < N; i++){
    //     setMem(level[aa][i], i, full[aa][i]);
    //     std::cout << "Added " << names[i] << " at " << level[aa][i] << std::endl;
    //     if( dist[aa][i] > 0 ){
    //         setMem(dLvl[aa][i], i, dist[aa][i]);
    //         std::cout << "Dist " << names[i] << " at " << dLvl[aa][i] << std::endl;
    //     }
    // }
    // for( int i = 0; i < N ; i++){
    //     //std::cout << i << ": ";
    //     for( int j = 0; j < N ; j++){
    //      //   if( dist[i][j] > 0 )
    //             std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
   
    // for( int i = 0; i < N ; i++){
    //     //std::cout << i << ": ";
    //     for( int j = 0; j < N ; j++){
    //      //   if( dist[i][j] > 0 )
    //             std::cout << dLvl[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    // //int p, int lvl, int** dist, int** dLvl
    // int min = findMin(aa, zz, zz, 0, dist, dLvl);
    // std::cout << min << std::endl;

    // for( int i = 0; i < N ; i++){
    //     if( dist[i][13] <= 0 )
    //         continue;
    //     std::cout << i << "("<< names[i] <<") ";
    // }
    // std::cout << std::endl;

    // int aa = portalByCode( mapper["AA"] );
    // int zz = portalByCode( mapper["ZZ"] );

   

    // std::cout << "Searching..." << std::endl;
    // int min = search(portalVisited, aa, 0, zz, 0, dist, 0);
    // std::cout << min << std::endl;




    // for( int i = 0; i < portals.size(); i++){
    //     std::cout << portals[i].x << ", " << portals[i].y << std::endl;
    // }

    // for(auto i = mapper.begin(); i != mapper.end(); ++i){
    //     std::cout << i->first << " => ";
    //     int pOut = portalLinks[i->second][0];
    //     int pIn  = portalLinks[i->second][1];
    //     if( pOut != -1 )
    //         std::cout << names[pOut] << " ";
    //     if( pIn != -1 )
    //         std::cout << names[pIn] << " ";
    //     // std::cout << pOut.x << ", " << pOut.y << " => " << pIn.x << ", " << pIn.y << std::endl;
    //     std::cout << std::endl;
    // }

    

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         std::cout << dist[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // int aa = mapper["AA"];
    // int zz = mapper["ZZ"];

    // std::cout << dist[aa][zz] << std::endl;

    return 0;
}
