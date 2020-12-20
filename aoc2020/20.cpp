#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <tuple>
#include <numeric>

std::vector<std::string> rotateImage(const std::vector<std::string>& img){
    int m = img.size();
    int n = img[0].size();
    std::vector<std::string> rotated ;
    for( int i = 0; i < n; i++ )
        rotated.push_back( std::string(m, '@'));
    
    for( int r = 0; r < n; r++)
        for( int k = 0; k < m; k++)
            rotated[r][k] = img[k][n - 1 - r];
        
    return rotated;
}

std::vector<std::string> flipImage(const std::vector<std::string>& img){
    std::vector<std::string> flipped ;
    for( int i = 0; i < img.size(); i++ ){
        std::string cpy(img[i]);
        std::reverse( begin(cpy), end(cpy) );
        flipped.push_back(cpy);
    }

    return flipped;
}

constexpr int N = 0, E = 1, S = 2, W = 3;
struct Tile {
    int link[4] = {0};
    int dir; //N, E, S, W
    std::vector<std::string> map;
    // These are for comparisons only
    std::string border[4]; 
    bool flipped;
    int id;

    void calcBorders() {
        dir = N;
        flipped = false;
        border[0] = std::string(map[0]);
        border[1] = std::string("**********");
        border[2] = std::string(map[9]);
        border[3] = std::string("**********");
        for( int i = 0; i < 10; i++){
            border[1][i] = map[i][9];
            border[3][i] = map[i][0];
        }
    }

    void rotCCW() {
        std::string tmp = border[0];
        int lTmp = link[0];
        for( int i = 0; i < 3; i++){
            border[i] = border[i + 1];
            link[i] = link[i + 1];
        }
        link[3] = lTmp;
        border[3] = tmp;

        std::reverse( begin(border[1]), end(border[1]) );
        std::reverse( begin(border[3]), end(border[3]) );
        dir = (dir + 1) % 4;
    }

    const std::string& borderAt(int d){
        return border[d];
    }

    void flip() {
        flipped = !flipped;

        if( dir == E || dir == W ) //If it's east or west, switch the dir
            dir = 4 - dir; 
        
        std::string tmp =  border[1];
        border[1] = border[3];
        border[3] = tmp;
        std::reverse( begin(border[0]), end(border[0]) );
        std::reverse( begin(border[2]), end(border[2]) );

        int lTmp = link[1];
        link[1] = link[3];
        link[3] = lTmp;
    }

    bool alignLinks(int top, int left) {
        for( int f = 0; f < 2; f++){
            for( int r = 0; r < 4; r++ ){
                if( link[N] == top && link[W] == left )
                    return true;
                rotCCW();
            }
            flip();
        }
        return false;
    }

    void orientMap() {
        if( flipped )
            map = flipImage(map);
        flipped = false;

        for( ; dir > 0; dir--)
            map = rotateImage(map);
    }

    bool matchAndLink(Tile& other){
        for( int f = 0; f < 2; f++ ){
            for( int r = 0; r < 4; r++){
                for( int i = 0; i < 4; i++){
                    if( borderAt(0).compare(other.borderAt(2)) == 0 ){ //Match !
                        link[0] = other.id;
                        other.link[2] = id;
                        return true;
                    }
                    other.rotCCW();
                }
                rotCCW();
            }
            flip();
        }
        return false;
    }

    bool isCorner() {
        int total = 0;
        for( int i = 0; i < 4; i++)
            total+= link[i] != 0;
        return total == 2;
    }
};

std::unordered_map<int, Tile> loadTiles() {
    std::unordered_map<int, Tile> tiles;
    std::string word;
    while( std::cin >> word >> word  ){
        int id = atoi(word.substr(0, word.size() - 1).c_str());
        Tile t;        
        t.id = id;

        for( int i = 0; i < 10; i++){
            std::cin >> word; 
            t.map.push_back(word);
        }
        t.calcBorders();
        tiles[id] = t;
    }

    for( auto it : tiles )
        for( auto jt : tiles )
            if( it.first != jt.first )
                tiles[it.first].matchAndLink(tiles[jt.first]);
        
    return tiles;
}
// ---- Part 1 ----
void part1() {
    std::unordered_map<int, Tile> tiles = loadTiles();
    int64_t mult = 1;
    for( auto it : tiles )        
        if( it.second.isCorner() )
            mult *= it.first;
    
    std::cout << mult << std::endl;
}
// ---- Part 2 ----
bool markMonsterAt(int r, int c, std::vector<std::string>& map, const std::vector<std::string>& monster){
    for( int i = 0; i < monster.size(); i++ )
        for( int j = 0; j < monster[0].size(); j++)
            if( monster[i][j] == '#' && map[r + i][c+ j] == '.' )
                return false;

    for( int i = 0; i < monster.size(); i++ )
        for( int j = 0; j < monster[0].size(); j++)
            if( monster[i][j] == '#')
                map[r + i][c+ j] = 'O';

    return true;
}

int markMonsters(std::vector<std::string>& map, const std::vector<std::string>& monster){
    int m = monster.size();
    int n = monster[0].size();
    int count = 0;
    for( int i = 0; i <= map.size() - m ; i++)
        for( int j = 0; j <= map[0].size() - n ; j++)
            if( markMonsterAt(i, j, map, monster) )
                count++;

    return count;
}

int countHash(const std::vector<std::string>& pic){
    int count = 0;
    for( int i = 0; i < pic.size(); i++ )
        for( int j = 0; j < pic[0].size(); j++)
            if( pic[i][j] == '#')
                count++;

    return count;
}

void part2() {
    std::unordered_map<int, Tile> tiles = loadTiles();
// Find any corner
    int NW = 0;
    for( auto it : tiles )
        if( it.second.isCorner() ){
            NW = it.first;
            break;
        }

// Align from NW to SE
    int SIZE = (int) std::sqrt( tiles.size() );
    std::vector< std::vector<int> > tileMap;

    int t = NW;
    for( int r = 0; r < SIZE; r++){
        std::vector<int> row;
        int top = 0, left = 0;
        for( int c = 0; c < SIZE; c++){
            if( r != 0 )
                top = tileMap[r - 1][c];
            tiles[t].alignLinks(top, left);
            row.push_back(t);
            left = t;
            t = tiles[t].link[E];
        }
        tileMap.push_back( row );
        t = tiles[row[0]].link[2];
    }
// Merge tiles
    std::vector< std::string > pic;
    int picTileSize = tiles[NW].map.size() - 2;
    for( int i = 0; i < SIZE * picTileSize; i++)
        pic.push_back( std::string(picTileSize * SIZE, '@'));

    for( int i = 0; i < SIZE; i++){
        for( int j = 0; j < SIZE; j++) {
            Tile t = tiles[ tileMap[i][j] ];
            t.orientMap();
            int r0 = i * picTileSize;
            int c0 = j * picTileSize;
            for( int r = 0; r < picTileSize; r++){
                for( int c = 0; c < picTileSize; c++)
                    pic[r0 + r][c0 + c] = t.map[r + 1][c + 1];
            }
        }
    }
// Load monster image
    std::vector<std::string> monsterPic;
    monsterPic.push_back("                  # ");
    monsterPic.push_back("#    ##    ##    ###");
    monsterPic.push_back(" #  #  #  #  #  #   ");
// Find monsters
    for( int f = 0; f < 2; f++ ){
        for(int i = 0; i < 4; i++){
            if( markMonsters(pic, monsterPic) != 0 ){
                std::cout << countHash(pic) << std::endl;
                return;
            }
            monsterPic = rotateImage(monsterPic);
        }
        monsterPic = flipImage(monsterPic);
    }
}

int main() {
    part2();
}