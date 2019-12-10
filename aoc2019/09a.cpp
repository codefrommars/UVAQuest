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

struct Machine{
    int status; //Blocked = 1, Halted = 2.
    int relativeBase;
    int pp;
    __int64* ram;
    std::deque<__int64> in_pin;
    std::deque<__int64>* out_pin;
};

__int64 getParam(Machine * m, int pIndex){
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

void setParam(Machine *m, int pIndex, __int64 value ){
    size_t c = m->ram[m->pp + pIndex];
    int accessMode = mode(m->ram[m->pp], pIndex);
    
    if( accessMode == 2 ){
        c += m->relativeBase;
    }

    m->ram[c] = value;
}


void add(Machine *m){

    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a + b);

    m->pp += 4;
}

void mul(Machine* m ){

    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a * b);

    m->pp += 4;
}

void in(Machine* m){
    if( m->in_pin.size() == 0 ){
        m->status = 1; //Blocked
        return;
    }

    setParam(m, 1, m->in_pin.front());
    m->in_pin.pop_front();

    m->pp += 2;
    m->status = 0;
}

void out(Machine *m){
    __int64 a = getParam(m, 1);
    m->out_pin->push_back(a);
    m->pp += 2;
}

void jnz(Machine *m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);

    if( a != 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void jz(Machine* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);

    if( a == 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void lt(Machine* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a < b );
        
    m->pp += 4;
}

void eq(Machine* m){
    __int64 a = getParam(m, 1);
    __int64 b = getParam(m, 2);
    setParam(m, 3, a == b );

    m->pp += 4;
}

void rel(Machine* m){
    size_t a = (size_t)getParam(m, 1);
    m->relativeBase += a;
    m->pp += 2;
}

typedef void (*OPPointer)(Machine* ) ;

OPPointer op[] = {
    0,
    add,
    mul,
    in,
    out,
    jnz,
    jz,
    lt,
    eq,
    rel
};

int run(Machine* m){
    do{
        if( m->ram[m->pp] == 99 ){
            m->status = 2; //halted
            break;
        }
        op[ m->ram[m->pp] % 100 ](m);
    }while( m->status == 0 );
    return m->status;
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

    Machine m;
    std::deque<__int64> output;

    m.relativeBase = 0;
    m.ram = new __int64[ 1024 * 1024 ];
    m.out_pin = &output;
    
    
    m.status = 0;
    m.pp = 0;
    m.in_pin.clear();
    std::copy(rom.begin(), rom.end(), m.ram);
    m.in_pin.push_back(1);

    int retCode = run(&m);

    for( int i = 0; i < output.size(); i++){
        std::cout << output[i] << std::endl;
    }

    
    return 0;
}