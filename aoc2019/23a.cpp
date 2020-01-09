#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>


int mode(int opcode, int rParam){
    int modif = opcode / 100;
    int tenP = std::pow(10, rParam - 1);

    return (modif / tenP) % 10;
}

struct Network;

struct Computer{
    int status; //Blocked = 1, Halted = 2.
    int relativeBase;
    int pp;
    __int64* ram;
    //std::deque<__int64>* out_pin;
    //__int64 out_pin;

    //Problem specific
    std::deque<__int64> in_pin;
    std::deque<__int64> out_pin;

    //Network* net;
    //int out_pin;
};

struct Network{
    Computer* computers[50];
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

    int v = -1;

//Doesn't block
    if( m->in_pin.size() > 0 ){
        v = m->in_pin.front();
        m->in_pin.pop_front();
    }
    setParam(m, 1, v);

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
    m->out_pin.push_back(a);
    m->pp += 2;

    // a = getParam(m, 1);    
    // m->out_pin.push_back(a);
    // m->pp += 2;
    
    // a = getParam(m, 1);    
    // m->out_pin.push_back(a);
    // m->pp += 2;

    //std::cout << ( (m->ram[m->pp] % 100) == 4 ) << std::endl;
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

void startComputer(Computer* comps, std::vector<__int64> rom, int i){    
    comps[i].relativeBase = 0;
    comps[i].ram = new __int64[ 1024 * 100]; // Large Ram
    std::copy(rom.begin(), rom.end(), comps[i].ram);
    comps[i].in_pin.clear();
    comps[i].out_pin.clear();
    comps[i].status = 0;
    comps[i].pp = 0;

    //Set the Network number
    comps[i].in_pin.push_back( i );
}

int runOneOp(Computer* m){
    //std::cout << "Status " << m->status << std::endl;
    if( m->status != 0 )
        return - 1;
    
    if( m->ram[m->pp] == 99 ){
        m->status = 2; //halted
        return m->status;
    }
    //std::cout << "Running OP: " << m->ram[m->pp] << std::endl;
    op[ m->ram[m->pp] % 100 ](m);
    return m->status;
}
void sendPacket(Computer* comps, int address, int x, int y){

    comps[address].in_pin.push_back(x);
    comps[address].in_pin.push_back(y);
}

// int runComputers(Computer* comps, int n){
//     int running = n;
//     while( running > 0 ){
//         for( int i = 0; i < n; i++){
//             if( comps[i].status == 2 )
//                 continue;

//             int status = runOneOp(&comps[i]);
//             if( status == 2 )
//                 running--;
            
//             //Check the output buffer
//             if( comps[i].out_pin.size() >= 3 ){
//                 int address = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
//                 int x = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
//                 int y = comps[i].out_pin.front(); comps[i].out_pin.pop_front();

//                 if( address == 255 )
//                     return y;
                
//                sendPacket(comps, address, x, y);
//             }
//         }
//     }

//     return -1;
// }

// int run(Computer* m){
//     do{
//         if( m->ram[m->pp] == 99 ){
//             m->status = 2; //halted
//             break;
//         }
//         op[ m->ram[m->pp] % 100 ](m);

//     }while( m->status == 0 );
//     return m->status;
// }


int constexpr N = 2;

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

    Computer comps[N];

    for( int i = 0; i < N; i++)
        startComputer(comps, rom, i);
    
    //std::cout << "Computers started" << std::endl;

    int running = N;
    while( running > 0 ){
        for( int i = 0; i < N; i++){

            if( comps[i].status == 2 )
                continue;
            //std::cout << "Run: " << i << std::endl;

            int status = runOneOp(&comps[i]);
            if( status == 2 ){
                running--;
                std::cout << i << " terminated." << std::endl;
                continue;
            }
        }

        for( int i = 0; i < N; i++){
            if( comps[i].out_pin.size() < 3 )
                continue;

            //Check the output buffer
            // if( comps[i].out_pin.size() >= 3 ){

                // int address = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
                // int x = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
                // int y = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
            int address = comps[i].out_pin[0];
            int x = comps[i].out_pin[1];
            int y = comps[i].out_pin[2];
            
            comps[i].out_pin.pop_front();
            comps[i].out_pin.pop_front();
            comps[i].out_pin.pop_front();

            // int x = comps[i].out_pin.front(); comps[i].out_pin.pop_front();
            // int y = comps[i].out_pin.front(); comps[i].out_pin.pop_front();

            std::cout << i << ": (" << x << ", " << y << ") -> " << address << std::endl;

            if( address >= N ){
                continue;
                // std::cout << x << std::endl;
                // std::cout << y << std::endl;
                //return 0;
            }
                
            sendPacket(comps, address, x, y);
            // }
        }
    }

    std::cout << "Message never sent (!)" << std::endl;

    // Computer m;  

    // m.relativeBase = 0;
    // m.ram = new __int64[ 1024 * 1024 ]; // Large Ram

    // m.in_pin.clear();
    // m.out_pin = 0;
    // m.status = 0;
    // m.pp = 0;
    
    return 0;
}