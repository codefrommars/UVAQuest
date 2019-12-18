#include <iostream>
#include <vector>
#include <string>

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

void findMoves(State &s, std::vector<Move> &moves, int x, int y, int dst, int bd) {

    for( int dir = 0; dir < 4; dir++ ){
        if( dir == bd )
            continue;
                
        int nx = x + DIRS[dir][0];
        int ny = y + DIRS[dir][1];

        if( s.map[ny][nx] >= 'a' && s.map[ny][nx] <= 'z' && !hasKey(s, s.map[ny][nx]) ){
            addMove(moves, nx, ny, dst + 1);            
            continue;
        }
        
        if( isBlocked(s, nx, ny) )
            continue;

        findMoves(s, moves, nx, ny, dst + 1, BACK[dir]);
    }
}

int getKeys(State &s, int x, int y, int dst) {

    if( s.keysLeft == 0 ){
       // std::cout << "Returning: "<< dst << std::endl;
        return dst;
    }
    
    //Find possibilities
    std::vector<Move> moves;
    findMoves(s, moves, x, y, 0, -1);

    int min = 1000000;

    for( int i = 0; i < moves.size(); i++ ){
        //perform move.
        char k = s.map[ moves[i].y ][ moves[i].x ];
        std::cout << k << ",";
        //std::cout << "Move: "<< moves[i].x << ", " << moves[i].y << ": " << moves[i].distance << std::endl;
        setKey(s, k, true );
        s.keysLeft --;

        int cost = getKeys(s, moves[i].x, moves[i].y, moves[i].distance + dst);

        if( cost < min )
            min = cost;

        setKey(s, k, false );
        s.keysLeft ++;
    }

    return min;
}

void computeCosts(std::vector< std::string > &input, std::vector< char > &keys, int x, int y) {

    for( int i = 0; i < keys.size(); i++ ){
        //computeCost(input, keys[i], x, y);
    }
}

int main() {

    std::vector< std::string > input;
    std::vector< char > keys;
    std::string line;

    int x, y;

    int h = 0;
    int w = 0;
    //int keys = 0;

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
                keys.push_back(line[i]);
            }
        }
        h++;
        input.push_back(line);
    }

    computeCosts(input, keys, x, y);

    // std::cout << x << ", " << y << ". Keys: " << keys << std::endl;

    // State s;
    // s.keysLeft = keys;
    // s.map = input;

    // int cost = getKeys(s, x, y, 0);

    // std::cout << "Cost: " <<  cost << std::endl;

    return 0;
}
