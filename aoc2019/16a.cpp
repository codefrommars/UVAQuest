#include <iostream>
#include <vector>

void fft(std::vector<int> list, std::vector<int> *out, int phase){
    int basep[4] = {0, 1, 0, -1};
    for( int i = 0; i < out->size(); i++){
        int outi = 0;
        int pMult = i + 1;
        int pLen = 4 * pMult;

        for( int j = 0; j < list.size(); j++){
            int pIndex = (j + 1) % pLen;
            int pat = basep[pIndex /  pMult];
            outi += list[j] * pat;
        }

        out->at(i) = std::abs(outi) % 10;
    }
}

int main() {
    char digit;
    std::vector<int> list;
    std::vector<int> out;

    while( std::cin >> digit ){
        list.push_back( digit - '0');
        out.push_back(digit - '0');
    }
    
    int phases = 100;

    for( int p = 0; p < phases; p++){
        fft(list, &out, 1);
        std::copy(out.begin(), out.end(), list.begin());
    }

    for(int i = 0; i < 8; i++)
        std::cout << list[i];
    std::cout << std::endl;

    return 0;
}