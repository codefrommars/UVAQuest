#include <iostream>
#include <vector>
#include <queue>
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

int get(int* ram, int& pp, int index){
    int m = ram[pp + index];
    //std::cout << "param: " << m << std::endl;
    if( mode(ram[pp], index) == 1 )
        return m;

    return ram[m];
}

void add(int *ram, int& pp ){

    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);
    int c = ram[pp + 3];//param(ram, pp, 3, 3);

    ram[c] = a + b;

    pp += 4;
}

void mul(int *ram, int& pp ){

    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);
    int c = ram[pp + 3];//param(ram, pp, 3, 3);

    ram[c] = a * b;

    pp += 4;
}

std::queue<int> inBuffer;

void in(int *ram, int& pp){
    int a = ram[pp + 1];//param(ram, pp, 1, 1);
    //std::cout << "read_to(" << a << "): 1" << std::endl;
    
    //ram[a] = 1; //ONLY FOR THIS PROGRAM
    //std::cin >> ram[a];
    ram[a] = inBuffer.front();
    inBuffer.pop();
    
    //std::cout << "in: " << ram[a] << std::endl;
    pp += 2;
}

int out_value = 0;

void out(int* ram, int& pp){
    int a = get(ram, pp, 1);
    out_value = a;
    //std::cout << "out: " << out_value << std::endl;
    pp += 2;
}

void jnz(int* ram, int& pp){
    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);

    if( a != 0 )
        pp = b;
    else
        pp += 3;
}

void jz(int* ram, int& pp){
    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);

    if( a == 0 )
        pp = b;
    else
        pp += 3;
}

void lt(int* ram, int& pp){
    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);
    int c = ram[pp + 3];

    ram[c] = a < b;
        
    pp += 4;
}

void eq(int* ram, int& pp){
    int a = get(ram, pp, 1);
    int b = get(ram, pp, 2);
    int c = ram[pp + 3];

    ram[c] = a == b;
        
    pp += 4;
}

typedef void (*OPPointer)(int* , int& ) ;

void run(int *ram){
    int pp = 0;

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

    while( ram[pp] != 99 ){
        op[ ram[pp] % 100 ](ram, pp);
    }
}

int runNounVerb(int noun, int verb, int *ram) {
    ram[1] = noun;
    ram[2] = verb;
    run(ram);
    return ram[0];
}

int runProgram(std::vector<int> &rom, int* ram, int amp, int signal){
    std::copy(rom.begin(), rom.end(), ram);
    inBuffer.push(amp);
    // std::cout << "push: " << input << std::endl;
    
    inBuffer.push(signal);
    // std::cout << "push: " << out_value << std::endl;

    // std::cout << "running program" << std::endl;
    run(ram);
    return out_value;
}

int digit5(int num, int index){
    int tenP = std::pow(5, index);
    return (num / tenP) % 5;
}


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

int evalSeq(int* seq, int n, std::vector<int> &rom, int* ram){
    int value = 0;
    for( int i = 0; i < n; i++){
        value = runProgram(rom, ram, seq[i], value);
    }        
    return value;
}

int maximize(int* seq, int n, int k, std::vector<int> &rom, int* ram){
    if( n == k ){
        return evalSeq(seq, n, rom , ram);
    }
    
    int max = 0;

    for( int j = k; j < n; j++){
        
        //std::cout << "swapping" << std::endl;
        //swap i, n
        swap( seq, k, j);

        int v = maximize( seq, n, k + 1, rom, ram);
        if( v > max ){
            max = v;
        }
        swap( seq, k, j);
    }

    return max;
}



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


    int a[] = { 0, 1, 2, 3, 4 };

    std::cout << "Rom size: " << rom.size() << std::endl;
    int* ram = new int[ rom.size() ];

    std::cout << maximize(a, 5, 0, rom, ram) << std::endl;
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

    // return 0;
}