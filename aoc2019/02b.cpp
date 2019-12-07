#include <iostream>
#include <vector>
#include <algorithm>


void add(int *ram, int& pp ){
    int a = ram[pp + 1];
    int b = ram[pp + 2];
    int c = ram[pp + 3];

    ram[c] = ram[a] + ram[b];

    pp += 4;
}

void mul(int *ram, int& pp ){
    int a = ram[pp + 1];
    int b = ram[pp + 2];
    int c = ram[pp + 3];

    ram[c] = ram[a] * ram[b];

    pp += 4;
}


void run(int *ram){
    int pp = 0;

    while( ram[pp] != 99 ){
        switch( ram[pp] ){
            case 1 :
                add(ram, pp);
                break;
            case 2 :
                mul(ram, pp);
                break;
        }
    }
}

int runNounVerb(int noun, int verb, int *ram) {
    ram[1] = noun;
    ram[2] = verb;
    run(ram);
    return ram[0];
}

int main(){
    std::vector<int> rom;

    for (int i; std::cin >> i;) {
        rom.push_back(i);
        if (std::cin.peek() == ',')
            std::cin.ignore();
    }

    int* ram = new int[ rom.size() ];

    for( int noun = 0; noun < 99; noun++){
        for( int verb = 0; verb < 99; verb++){
            std::copy(rom.begin(), rom.end(), ram);

            ram[1] = noun;
            ram[2] = verb;

            run(ram);

            if( ram[0] == 19690720 ){
                std::cout << (100 * noun + verb ) << std:: endl;
                return 0;
            }
        }
    }

    return 0;
}