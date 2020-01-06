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
    //__int64 out_pin;
    std::deque<__int64>* out_pin;

    //Problem specific
    std::deque<__int64> in_pin;
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

void in(Computer* m){
    // if( m->in_pin == 0 ){
    //     m->status = 1; //Blocked
    //     return;
    // }

    // setParam(m, 1, m->in_pin);
    

    // m->pp += 2;
    // m->status = 0;
     if( m->in_pin.size() == 0 ){
        m->status = 1; //Blocked
        return;
    }

    int v = m->in_pin.front();
    //std::cout << "Read: " << v << std::endl;
    setParam(m, 1, m->in_pin.front());
    m->in_pin.pop_front();

    m->pp += 2;
    m->status = 0;
}

int DIRS[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};
int BACK[4] = { 1, 0, 3, 2};

void out(Computer *m){
    __int64 a = getParam(m, 1);
    //std::cout << "Pushing : " << a << std::endl;
    //m->out_pin = a;

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

void runProgram(Computer &m, std::vector<__int64> &rom){ 
    m.relativeBase = 0;    
    std::copy(rom.begin(), rom.end(), m.ram);
    m.in_pin.clear();
    m.out_pin->clear();
    m.status = 0;
    m.pp = 0;

    constexpr int N = 14;

    std::string program[N] = {
        "OR E T",
        "AND F T",
        "AND G T",
        "NOT T T",
        "AND H T",
        "OR A J",
        "AND B J",
        "AND C J",
        "NOT J J",
        "AND D J",
        "AND T J",
        "NOT A T",
        "OR T J",
        "RUN"
    };
//Setup input
    for( int l = 0; l < N; l++){
        std::string p = program[l];
        for( int i = 0; i < p.size(); i++){
            m.in_pin.push_back( (int) p[i] );
        }
        m.in_pin.push_back( 10 ); //nl
    }

    if( run(&m) != 2 ){
        std::cout << "Code didn't finish correctly." << std::endl;
    }

    while( m.out_pin->size() > 0 ){
        if( m.out_pin->front() < 128 )
            std::cout << (char)m.out_pin->front();
        else
            std::cout << m.out_pin->front();
        m.out_pin->pop_front();
    }
    std::cout << std::endl;
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

    Computer m; 
    std::deque<__int64> out;
    m.ram = new __int64[ 1024 * 1024 ]; // Large Ram
    m.out_pin = &out;


    m.relativeBase = 0;
    std::copy(rom.begin(), rom.end(), m.ram);

    m.in_pin.clear();
    m.status = 0;
    m.pp = 0;

    runProgram(m, rom);    
    
    return 0;
}