#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 60

int findLeft(int* inventory, int n){
    for( int i = 1; i <= n; i++){
        if( inventory[i] < 0 ){
           return i;
        }
    }
    return 0;
}

int insert(std::map<std::string, int> &map, std::string k){
    if( map.count(k) == 0 )
        map[k] = map.size();
    return map[k];
}

void produce(int elm, int* inventory, int reactions[MAX][MAX], int n){
    std::cout << "Produce " << elm << std:: endl;
    while( inventory[elm] < 0 ){
        for( int i = 0; i <= n; i++){
            inventory[i] += reactions[elm][i];
        }
    }
    std::cout << "Completed production" << std:: endl;
}

int main(){
    char a[4], b[4];
    std::map<std::string, int> mapper;
    //std::vector<std::pair<int, int>> links;
    //int n = 0;
    //std::cout << "The matrix" << std::endl;
    mapper["ORE"] = 0;

    int reactions[MAX][MAX] = {};
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

    for(int j = 0; j <= n; j++){
        for(int i = 0; i <= n; i++){
            std::cout << reactions[j][i] << " ";
        }
        std::cout << std::endl;
    }

    int inventory[MAX];

    int ORE = mapper["ORE"];
    int FUEL = mapper["FUEL"];

    inventory[FUEL] = -1;

    int left = FUEL ;
    while( left != ORE ){        
        produce( left, inventory, reactions, n );
        left = findLeft(inventory, n);
    }

    std::cout << inventory[ORE] << std::endl;

    // std::cout << mapper["FUEL"] << " to " << mapper["ORE"] << std::endl;

    // for(int i = 0; i < MAX; i++){
    //     orbit[i] = new int[MAX];
    //         for( int j = 0; j < MAX; j++){
    //             orbit[i][j] = 0;
    //         }
    // }
    // while( scanf("%3s)%3s\n", &a, &b) != EOF ) {
    //     std::string sa(a);
    //     std::string sb(b);

    //     //std::cout << sa << "->"<< sb << std::endl;
    //     int f = insert(mapper, a);
    //     int t = insert(mapper, b);
    //     //std::cout << f << "->"<< t << std::endl;
    //     orbit[t][f] = 1;
        
    // }
    
    // std::cout << "Computing transitivity" << std::endl;
    // for(int k = 0; k < MAX; k++){
    //     for(int i = 0; i < MAX; i++){
    //         for( int j = 0; j < MAX; j++){
    //             if( orbit[i][k] && orbit[k][j] )
    //                 orbit[i][j] = 1;
    //         }
    //     }
    // }
    // int count = 0;
    // for(int i = 0; i < MAX; i++){
    //     for( int j = 0; j < MAX; j++){
    //         count += orbit[i][j];
    //     }
    // }

    // std::cout << count << std::endl;
    return 0;
}