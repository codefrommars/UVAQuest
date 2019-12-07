#include <iostream>
#include <vector>


int add(int *ram, int pp ){
    int a = ram[pp + 1];
    int b = ram[pp + 2];
    int c = ram[pp + 3];

    ram[c] = ram[a] + ram[b];

    return pp + 4;
}

int mul(int *ram, int pp ){
    int a = ram[pp + 1];
    int b = ram[pp + 2];
    int c = ram[pp + 3];

    ram[c] = ram[a] * ram[b];

    return pp + 4;
}


void run(int *ram){
    int pp = 0;

    while( ram[pp] != 99 ){
        switch( ram[pp] ){
            case 1 :
                pp = add(ram, pp);
                break;
            case 2 :
                pp = mul(ram, pp);
                break;
        }
    }

}

int main(){
    std::vector<int> ram;

    for (int i; std::cin >> i;) {
        ram.push_back(i);
        if (std::cin.peek() == ',')
            std::cin.ignore();
    }

    //1202
    ram[1] = 12;
    ram[2] = 2;
    run(&ram[0]);

    std::cout << ram[0] << std:: endl;

}