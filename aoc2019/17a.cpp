#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

struct Canvas {
    int* buffer;
    int* visited;
    int W;
    int H;

    int minx;
    int miny;
    int maxx;
    int maxy;


    void set(int x, int y, int value){
        buffer[y * W + x] = value;
        visited[y * W + x] = 1;
        if( x < minx )
            minx = x;
        if( x > maxx )
            maxx = x;
        if( y < miny )
            miny = y;
        if( y > maxy )
            maxy = y;
    }

    void setNew(int x, int y, int value){
        if( get(x, y) == -1 )
            set(x, y, value);
    }

    int get(int x, int y){
        return buffer[y * W + x];
    }

};


int mode(int opcode, int rParam){
    int modif = opcode / 100;
    int tenP = std::pow(10, rParam - 1);

    return (modif / tenP) % 10;
}



struct Computer{
    int status; //Blocked = 1, Halted = 2.
    int relativeBase;
    int pp;
    __int64* ram;
    std::deque<__int64>* out_pin;

    //Problem specific
    int in_pin;
    //int out_pin;
    Canvas* canvas;
    int px, py;

};

__int64 getParam(Computer * m, int pIndex){
    __int64 v = m->ram[m->pp + pIndex];
    int accessMode = mode(m->ram[m->pp], pIndex);

    switch( accessMode ){
        case 0 : //param mode
            return m->ram[ (size_t)v];
        
        case 1 : //immediate mode
            return v;
        
        case 2 : 
            return m->ram[(size_t)v + m->relativeBase];
    }
}

void setParam(Computer *m, int pIndex, __int64 value ){
    size_t c = m->ram[m->pp + pIndex];
    int accessMode = mode(m->ram[m->pp], pIndex);
    
    if( accessMode == 2 ){
        c += m->relativeBase;
    }

    m->ram[c] = value;
}


void add(Computer *m){

    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a + b);

    m->pp += 4;
}

void mul(Computer* m ){

    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a * b);

    m->pp += 4;
}

void findBallPaddle(Computer* m, int& ball, int& paddle ){
    Canvas c = *m->canvas;

    for( int j = c.miny; j <= c.maxy; j++){
        for( int i = c.minx; i <= c.maxx; i++){
            int tile = c.get(i, j);
            if( tile == 3 ){
                paddle = i;
            }else if( tile == 4 ){
                ball = i;
            }
            //std::cout << COL [ tile ];
        }
        //std::cout << std::endl;
    }
    //std::cout << "SCORE: " << m->score << std::endl<< std::endl;
}

void in(Computer* m){
    if( m->in_pin == 0 ){
        m->status = 1; //Blocked
        return;
    }

    setParam(m, 1, m->in_pin);
    

    m->pp += 2;
    m->status = 0;
}

int DIRS[5][2] = {
    {0, 0},
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

int BACK[5] = { 0, 2, 1, 4, 3};

char COL[5] = {'#', '.', 'O', 'S'};


void out(Computer *m){
    __int64 a = getParam(m, 1);
    m->out_pin->push_back(a);
    
    // int dir = m->in_pin;

    // int nx = m->px + DIRS[dir][0];
    // int ny = m->py + DIRS[dir][1];

    // // std::cout << nx  << ", " << ny << std::endl;
    // //Draw to canvas
    // switch( a ){ //Blocked couldn't move
    //     case 0:
    //         m->canvas->setNew(nx, ny, a);
    //         break;
    //     case 2:
    //         // std::cout << "Found 2" << std::endl;
    //     case 1:
    //         m->canvas->setNew( m->px, m->py, a);
    //         m->px = nx;
    //         m->py = ny;
    //         break;
    // }
    
    // m->out_pin = a;
    // m->in_pin = 0;
    m->pp += 2;
}

void jnz(Computer *m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);

    if( a != 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void jz(Computer* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);

    if( a == 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void lt(Computer* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a < b );
        
    m->pp += 4;
}

void eq(Computer* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a == b );

    m->pp += 4;
}

void rel(Computer* m){
    size_t a = (size_t)getParam(m, 1);
    m->relativeBase += a;
    m->pp += 2;
}

typedef void (*OPPointer)(Computer* ) ;

OPPointer op[] = {
    0,
    add,
    mul,
    in,//in,
    out,
    jnz,
    jz,
    lt,
    eq,
    rel
};


int run(Computer* m){
    do{
        if( m->ram[m->pp] == 99 ){
            m->status = 2; //halted
            break;
        }
        op[ m->ram[m->pp] % 100 ](m);

    }while( m->status == 0 );
    return m->status;
}

int findAlignParams(std::vector< std::vector<char> > &view , int w, int h){
    int sum = 0;
    for( int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if ( view[j][i] == '#' ){
                if( i == 0 || j == 0 || i == w - 1 || j == h - 1 )
                    continue;
                
                if( view[j-1][i] == '#' && view[j+1][i] == '#' && view[j][i - 1] == '#' && view[j][i+1] == '#'){
                    sum += i * j;
                    std::cout << i << ", " << j << std::endl;
                }
            }
        }
    }
    return sum;
}


int main(){

    std::vector<__int64> rom;

    for (__int64 i; std::cin >> i;) {
        rom.push_back(i);
        if (std::cin.peek() == ',')
            std::cin.ignore();
        else
        {
            break;
        }
    }

    // Canvas c;
    // c.W = 1000;
    // c.H = 1000;
    // c.buffer = new int[c.W * c.H];
    // c.visited = new int[c.W * c.H];
    // c.minx = 999999;
    // c.maxx = -1;
    // c.miny = 999999;
    // c.maxy = -1;

    // for( int i = 0; i < c.W * c.H; i++){
    //     c.buffer[i] = -1;
    //     c.visited[i] = 0;
    // }
    Computer m;
    std::deque<__int64> output;


    // m.canvas = &c;
    // m.px = 500;
    // m.py = 500;
    //c.set(500, 500, 1);

    m.relativeBase = 0;
    m.ram = new __int64[ 1024 * 1024 ]; // Large Ram
    std::copy(rom.begin(), rom.end(), m.ram);

    m.in_pin = 0;
    m.out_pin = &output;
    
    
    m.status = 0;
    m.pp = 0;

    run(&m);

    int w = -1;
    int h = 0;
    bool s = false;
    std::vector< std::vector<char> > view;
    view.push_back( std::vector<char>() );
    //int y = 0, x = 0;
    for( int i = 0; i < output.size(); i++){
        
        //s = output[i] != 10 | s;
        //s = (output[i] != 10) | s;
        if( output[i] == 10 && i != output.size() - 1){
            if( w == -1 )
                w = i;
            //if( s )
            h++;
            s = false;
            //y++;
            view.push_back( std::vector<char>() );
        }else{
            view[h].push_back( (char)output[i] );
        }
    }
    //char** view = new char[h][w];
    for(int j = 0; j < view.size(); j++){
        for( int i = 0; i < view[j].size(); i++ ){
            std::cout << view[j][i];
        }
        std::cout << std::endl;
    }

    std::cout << findAlignParams(view, w, h) << std::endl;
    // for( int i = 0; i < output.size(); i++){ 
    //     //std::cout << (char)output[i];
    // }
    //std::cout << w << ", " << h << std::endl;

    // explore(&m, 0, 1, 0);

    // int ox, oy;
    // for( int j = c.miny; j <= c.maxy; j++){
    //     for( int i = c.minx; i <= c.maxx; i++){
    //         if( c.get(i, j) == 2 ){
    //             ox = i;
    //             oy = j;
    //         }
    //         // std::cout << COL [ c.get(i, j) ];
    //     }
    //     // std::cout << std::endl;
    // }

    

    // int time = fill(&c, ox, oy);
    // for( int j = c.miny; j <= c.maxy; j++){
    //     for( int i = c.minx; i <= c.maxx; i++){
    //         std::cout << COL [ c.get(i, j) ];
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << time << std::endl;


    // m.ram[0] = 2;

    // do{
    //     run(&m);
    // }while( countBlocks(c) > 0 );
    
    //  std::cout << m.score << std::endl;
    
    
    return 0;
}