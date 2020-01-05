#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>



/*

abcacdeabcacdebecbeccdeabcacdebec

A,B,A,B,C,C,B,A,B,C
abca = A
L,12,L,10,R,8,L,12
cde = B
R,8,R,10,R,12
bec = C
L,10,R,12,R,8

*/
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
    //std::deque<__int64>* out_pin;
    __int64 out_pin;

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
    std::cout << "Read: " << v << std::endl;
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
    m->out_pin = a;
    
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

int findRobot(std::vector< std::vector<char> > &view, int &x, int &y){
    //^, v, <, or >
    char robot[4] = {'^', 'v', '<', '>'};

    for(int j = 0; j < view.size(); j++){
        for( int i = 0; i < view[j].size(); i++ ){
            if( view[j][i] != '#' && view[j][i] != '.' ){
                x = i;
                y = j;
                for( int d = 0; d < 4; d++)
                    if( robot[d] == view[j][i] )
                        return d;
            }
        }
    }
    return -1;
}
//^, v, <, >
char findRotation(int rd, int d){
    char L = 'L';
    char R = 'R';
    switch( rd ){
        case 0 : //up
            if( d == 2 )
                return L;
            else
                return R;
        case 1:
            if( d == 2 )
                return R;
            else
                return L;
        case 2 : //up
            if( d == 0 )
                return R;
            else
                return L;
        case 3:
            if( d == 0 )
                return L;
            else
                return R;
    }
    return -1;
}

int followScaffold(std::vector< std::vector<char> > &view, int rx, int ry, int rd, int bd, int w, int h){
    for(int d = 0; d < 4; d++){
        if( d == bd )
            continue;

        int c = 0;
        while( true ){
            int nx = DIRS[d][0] + rx;
            int ny = DIRS[d][1] + ry;
            
            if( nx >= w || nx < 0 || ny >= h || ny < 0 || view[ny][nx] != '#' )
                break;
            c++;
            rx = nx;
            ry = ny;
        }
        if( c != 0 ){
            std::cout << findRotation(rd, d) << "," << c << std::endl;
            return followScaffold(view, rx, ry, d, BACK[d], w, h);
        }
    }
    return 1;
}

void showScaffold(std::vector< std::vector<char> > &view, int w, int h){
    int rx, ry;
    int rd = findRobot(view, rx, ry);
    //std::cout << rx << ", " << ry << ", " << rd << std::endl;

    //Follow the scaffold.
    //for(int i = 0; i < 4; i++){
    followScaffold(view, rx, ry, rd, 0, w, h);
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
    

    m.relativeBase = 0;
    m.ram = new __int64[ 1024 * 1024 ]; // Large Ram

    m.in_pin.clear();
    m.out_pin = 0;
    m.status = 0;
    m.pp = 0;

    //Setup input
    int points = 0;
    for( int y = 0; y < 50; y++){
        for( int x = 0; x < 50; x++){
            m.relativeBase = 0;
            std::copy(rom.begin(), rom.end(), m.ram);
            m.in_pin.clear();
            m.out_pin = 0;
            m.status = 0;
            m.pp = 0;
            // std::cout << "Pushing " << x << ", " << y << std::endl;
            m.in_pin.push_back( x );
            m.in_pin.push_back( y );
            if( run(&m) != 2 ){
                std::cout << "Code didn't finish correctly." << std::endl;
            }
            points += m.out_pin;
        }
    }


    std::cout << points << std::endl;

    
    return 0;
}