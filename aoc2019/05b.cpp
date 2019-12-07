#include <iostream>
#include <vector>
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

void in(int *ram, int& pp){
    int a = ram[pp + 1];//param(ram, pp, 1, 1);
    //std::cout << "read_to(" << a << "): 1" << std::endl;
    
    //ram[a] = 1; //ONLY FOR THIS PROGRAM
    std::cin >> ram[a];

    pp += 2;
}

void out(int* ram, int& pp){
    int a = get(ram, pp, 1);
    std::cout << a << std::endl;

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
        //std::cout << "code: " << ram[pp] << std::endl;
        op[ ram[pp] % 100 ](ram, pp);
        // switch( ram[pp] % 100 ){
        //     case 1 :
        //         add(ram, pp);
        //         break;
        //     case 2 :
        //         mul(ram, pp);
        //         break;
        //     case 3 :
        //         in(ram, pp);
        //         break;
        //     case 4 :
        //         out(ram, pp);
        //         break;
        //     case 4 :
        //         out(ram, pp);
        //         break;
        //     case 4 :
        //         out(ram, pp);
        //         break;
        //     case 4 :
        //         out(ram, pp);
        //         break;
        //     case 4 :
        //         out(ram, pp);
        //         break;
        // }
    }
}

int runNounVerb(int noun, int verb, int *ram) {
    ram[1] = noun;
    ram[2] = verb;
    run(ram);
    return ram[0];
}

int main(){
    // int opcode = 1101;

    // std::cout << mode(opcode, 1) << std::endl;
    // std::cout << mode(opcode, 2) << std::endl;
    // std::cout << mode(opcode, 3) << std::endl;
    
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
    //std::cout << "Rom size: " << rom.size() << std::endl;
    int* ram = new int[ rom.size() ];
    std::copy(rom.begin(), rom.end(), ram);
    //std::cout << "Running diagnostic " << std::endl;
    run(ram);

    // for( int noun = 0; noun < 99; noun++){
    //     for( int verb = 0; verb < 99; verb++){
    //         std::copy(rom.begin(), rom.end(), ram);

    //         ram[1] = noun;
    //         ram[2] = verb;

    //         run(ram);

    //         if( ram[0] == 19690720 ){
    //             std::cout << (100 * noun + verb ) << std:: endl;
    //             return 0;
    //         }
    //     }
    // }

    return 0;
}