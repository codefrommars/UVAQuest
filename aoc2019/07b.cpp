#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

int mode(int opcode, int rParam){
    //std::string str = std::to_string(ram[pp]);
    //return str[rParam] - '0';
    int modif = opcode / 100;
    //std::cout << "param: " << m << std::endl;
    int tenP = std::pow(10, rParam - 1);

    return (modif / tenP) % 10;
}

struct Machine{ 
    int index;
    int status; //Blocked = 1, Halted = 2.
    int pp;
    int* ram;
    std::deque<int> in_pin;
    std::deque<int>* out_pin;
};

int get(Machine * m, int index){
    int v = m->ram[m->pp + index];
    //std::cout << "param: " << m << std::endl;
    if( mode(m->ram[m->pp], index) == 1 )
        return v;

    return m->ram[v];
}



void add(Machine *m){

    int a = get(m, 1);
    int b = get(m, 2);
    int c = m->ram[m->pp + 3];//param(ram, pp, 3, 3);

    m->ram[c] = a + b;

    m->pp += 4;
}

void mul(Machine* m ){

    int a = get(m, 1);
    int b = get(m, 2);
    int c = m->ram[m->pp + 3];//param(ram, pp, 3, 3);

    m->ram[c] = a * b;

    m->pp += 4;
}

std::deque<int> inBuffer;

void in(Machine* m){
    int a = m->ram[m->pp + 1];
    
    if( m->in_pin.size() == 0 ){
        m->status = 1; //Blocked
        //std::cout << "Blocked: " << m->index << std::endl;
        return;
    }

    m->ram[a] = m->in_pin.front();
    m->in_pin.pop_front();
    
    //std::cout << "Read: " << m->ram[a] << std::endl;
    m->pp += 2;
    m->status = 0;
}

//int out_value = 0;

void out(Machine *m){
    int a = get(m, 1);
    m->out_pin->push_back(a);
   // std::cout << "Wrote: " << a << std::endl;
    //out_value = a;
    //std::cout << "out: " << out_value << std::endl;
    m->pp += 2;
}

void jnz(Machine *m){
    int a = get(m, 1);
    int b = get(m, 2);

    if( a != 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void jz(Machine* m){
    int a = get(m, 1);
    int b = get(m, 2);

    if( a == 0 )
        m->pp = b;
    else
        m->pp += 3;
}

void lt(Machine* m){
    int a = get(m, 1);
    int b = get(m, 2);
    int c = m->ram[m->pp + 3];

    m->ram[c] = a < b;
        
    m->pp += 4;
}

void eq(Machine* m){
    int a = get(m, 1);
    int b = get(m, 2);
    int c = m->ram[m->pp + 3];

    m->ram[c] = a == b;
        
    m->pp += 4;
}

typedef void (*OPPointer)(Machine* ) ;

// void run(int *ram){
//     int pp = 0;

//     OPPointer op[] = {
//         0,
//         add,
//         mul,
//         in,
//         out,
//         jnz,
//         jz,
//         lt,
//         eq
//     };

//     while( ram[pp] != 99 ){
//         op[ ram[pp] % 100 ](ram, pp);
//     }

//     std::cout << "op: " << ram[pp] << std::endl;
// }

OPPointer op[] = {
    0,
    add,
    mul,
    in,
    out,
    jnz,
    jz,
    lt,
    eq
};

int run(Machine* m){
    //std::cout << "R " << m->index << std::endl;
    do{
        if( m->ram[m->pp] == 99 ){
            m->status = 2; //halted
            break;
        }

        op[ m->ram[m->pp] % 100 ](m);

    }while( m->status == 0 );
    //std::cout << "P " << m->index << " status: " << m->status << std::endl;
    return m->status;
}


// int runProgram(std::vector<int> &rom, int* ram, int amp, int signal){
    
//     // std::cout << "push: " << input << std::endl;
    
//     inBuffer.push_back(signal);
//     // std::cout << "push: " << out_value << std::endl;

//     run(ram);
//     std::cout << "Program completed" << std::endl;
//     return out_value;
// }

// int digit5(int num, int index){
//     int tenP = std::pow(5, index);
//     return (num / tenP) % 5;
// }


void swap (int *v, int i, int j) {
	int t = v[i];
	v[i] = v[j];
	v[j] = t;
}

void perm(int* seq, int n, int k){
    if( n == k ){
        std::cout << seq << std::endl;
        return;
    }
        
    for( int j = k; j < n; j++){
        
        //std::cout << "swapping" << std::endl;
        //swap i, n
        swap( seq, k, j);

        perm( seq, n, k + 1);

        swap( seq, k, j);
    }
}

// int evalSeq(int* seq, int n, std::vector<int> &rom, int* ram){
//     int value = 0;
//     // for( int i = 0; i < n; i++){
//     //     value = runProgram(rom, ram, seq[i], value);
//     // }        
//     return value;
// }


int runSeq(int* seq, int n, std::vector<int> &rom, Machine* amps){
    for(int i = 0; i < n; i++){
        amps[i].status = 0;
        amps[i].pp = 0;
        amps[i].in_pin.clear();
        amps[i].in_pin.push_back(seq[i]);
        std::copy(rom.begin(), rom.end(), amps[i].ram);
    }

    amps[0].in_pin.push_back(0);

    int running = n;
    while( running > 0 ){
        for( int i = 0; i < n; i++ ){
            //std::cout << "Status: " << amps[i].status << std::endl;
            if( amps[i].status != 2 ){
                //amps[i].status = 0;
                if( run(&amps[i]) == 2 ){
                    running--;
                    //std::cout << "Machine " << amps[i].index << " finished. Still running: "<< running << std::endl;
                    // if( running == 0 ){
                    //     int ret = amps[4].out_pin->back();
                    //     std::cout << "returning " << ret << std::endl;
                    //     return ret;
                    // }
                }
            }
        }
    }

    //int ret = amps[AMPS - 1].out_pin->back();
    //std::cout << "returning " << ret << std::endl;

    return amps[n - 1].out_pin->back();
}

int maximize(int* seq, int n, int k, std::vector<int> &rom, Machine* amps){
    if( n == k ){
        return runSeq(seq, n, rom, amps);
    }
    
    int max = 0;

    for( int j = k; j < n; j++){
        
        //std::cout << "swapping" << std::endl;
        //swap i, n
        swap( seq, k, j);

        int v = maximize( seq, n, k + 1, rom, amps);
        if( v > max ){
            max = v;
        }
        swap( seq, k, j);
    }

    return max;
}


    // int status; //Blocked = 1, Halted = 2.
    // int pp;
    // int* ram;
    // std::deque<int> in_pin;
    // std::deque<int>* out_pin;



#define AMPS    5

int main(){
    
    //perm(a, 4, 0); 

    std::vector<int> rom;

    for (int i; std::cin >> i;) {
        rom.push_back(i);
        if (std::cin.peek() == ',')
            std::cin.ignore();
        else
        {
                break;
        }
        
    }



    Machine amps[AMPS];
    for(int i = 0; i < AMPS; i++){
        amps[i].index = i;
        amps[i].ram = new int[ rom.size() ];
        amps[i].out_pin = &(amps[ (i + 1) % AMPS ].in_pin);
    }

    std::cout << &amps[0].in_pin << " : " << amps[4].out_pin << std::endl;

    int seq[5] = { 5, 6, 7, 8, 9 };
    
    int out = maximize(seq, 5, 0, rom, amps);//runSeq(seq, 5, rom, amps);
    std::cout << "Completed: "<< out << std::endl;
    //int* ram = new int[ rom.size() ];

    //inBuffer.push_back(9);
    //int p = runProgram(rom, ram, 9, 0);
    //out = runProgram(rom, ram, 8, out);
    // out = runProgram(rom, ram, 7, out);
    // out = runProgram(rom, ram, 6, out);
    // out = runProgram(rom, ram, 5, out);


    // int a[] = { 0, 1, 2, 3, 4 };

    // std::cout << "Rom size: " << rom.size() << std::endl;
    // std::cout << maximize(a, 5, 0, rom, ram) << std::endl;
    // int max = -1;
    // int maxIndex = -1;

    // for(int i = 0; i < 5; i++){
    //     out_value = 0;
    //     //std::cout << i << std::endl;
    
    //     for(int index = 4; index >= 0; index -- ){
    //         int amp = digit5(i, index);
    //         //std::cout << ina;            
    //         out_value = runProgram(rom, ram, amp, out_value);
    //      }
    //      std::cout << ": " << out_value << std::endl;
    //     //std::cout <<  i << ": " << out_value << std::endl;
    
    //     if( out_value > max ){
    //         maxIndex = i;
    //         max = out_value;
    //      }
    // }

    // std::cout << maxIndex << ": " << max << std::endl;
    return 0;
}