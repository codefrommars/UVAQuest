#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 60
std::map<std::string, int> mapper;

int insert(std::map<std::string, int> &map, std::string k){
    if( map.count(k) == 0 )
        map[k] = map.size();
    return map[k];
}

int refill(int elm, __int64* inventory, __int64 reactions[MAX][MAX], int n){
    __int64 toProduce = std::abs(inventory[elm]);
    __int64 times = std::ceil( (double)toProduce / (double)reactions[elm][elm] );


    int left = 0 ;
    for( int i = 0; i <= n; i++){
        inventory[i] += times * reactions[elm][i];
        if( (i != 0) && (inventory[i] < 0) && (left == 0) ){
            left = i;
        }
    }

    return left;
}

__int64 produceFuel(_int64 k, __int64* inventory, __int64 reactions[MAX][MAX], int n, bool clear){
    if( clear ) {
        for( int i = 0; i <= n; i++){
            inventory[i] = 0;
        }
    }

    int ORE = mapper["ORE"];
    int FUEL = mapper["FUEL"];
    inventory[ORE] = 0;
    inventory[FUEL] = -k;

    int left = FUEL;

    while( left != ORE ){        
        left = refill( left, inventory, reactions, n );
        //  findLeft(inventory, n);
    }

    return inventory[ORE] * -1;
}

__int64 binSearch(__int64 l, __int64 r, __int64 value, __int64* inventory, __int64 reactions[MAX][MAX], int n){

    if( l == r )
        return l;

    __int64 m = (l + r ) / 2;
    __int64 mVal = produceFuel(m, inventory, reactions, n, true);

    if( l == m )
        return m;

    if( mVal < value ){
        return binSearch(m, r, value, inventory, reactions, n);
    }else if( mVal > value ){
        return binSearch(l, m, value, inventory, reactions, n);
    }

    return m;
}

int main(){
    char a[4], b[4];
    mapper["ORE"] = 0;

    __int64 reactions[MAX][MAX] = {};
    std::vector< std::vector<std::string> > tokenLines;
    std::string line;
    char* special = " ,=>";
    int n = 0;
    while( std::getline(std::cin, line) ){
        std::vector<int> tokens;
        int tokNum = 0;
        for (auto i = strtok(&line[0], special); i != NULL; i = strtok(NULL, special)){
            int value = -1;
            if( tokNum % 2 == 1 ){
                value = insert(mapper, i);
            }else{
                value = std::stoi(i);
            }
            tokNum++;
            // std::cout << value << " ";
            tokens.push_back(value);
        }
        //Line for: last token 
        int j = tokens[ tokens.size() - 1 ];
        tokens[tokens.size() - 2 ] = tokens[tokens.size() - 2 ] * -1;

        for( int i = 0 ; i < tokens.size() ; i += 2) {
            int v = tokens[i];
            int c = tokens[i + 1];
            reactions[j][c] = -1 * v;
        }
        n++;
    }

    __int64 ore = 1000000000000;

    __int64 inventory[MAX] = {} ;
    //Estimate max ore
    __int64 cost = 0;
    __int64 k = 1;
    while( cost < ore ){
        k *= 2;
        cost = produceFuel(k, inventory, reactions, n, true);
    }

    __int64 l = k / 2;
    __int64 r = k;

    __int64 v = binSearch(l, r, ore, inventory, reactions, n);
    std::cout << v << std::endl;
    
    return 0;
}