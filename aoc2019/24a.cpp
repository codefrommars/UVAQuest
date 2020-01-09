
#include <iostream>
#include <map>



int bioRating(int* state){
    __int32 value = 0;
    for( int i = 0; i < 25; i++)
        value += state[i] << i;
    return value;
}

int bugAt(int* state, int i){
    if( i < 0 || i >= 25 )
        return 0;
    return state[i];
}

int adjacent(int* state, int i){
    //up and down, no problem
    int u = bugAt(state, i - 5);
    int d = bugAt(state, i + 5);

    int row = i / 5;
    int l = 0;
    //left and right only if remains in same row
    if( (i - 1) / 5 == row )
        l = bugAt(state, i - 1);
    
    int r = 0;
    if( (i + 1) / 5 == row )
        r = bugAt(state, i + 1);

    return u + d + l + r;
}

int adj[25];

int next(int* state){
    for(int i = 0; i < 25; i++)
        adj[i] = adjacent(state, i);
    
    for(int i = 0; i < 25; i++){
        if( state[i] == 1 && adj[i] != 1 ){
            state[i] = 0;
            continue;
        }
        if( state[i] == 0 && (adj[i] == 1 || adj[i] == 2) )
            state[i] = 1;
    }

    return bioRating(state);
}

int main(){
    std::map<int, int> record;
    int iteration = 0;

    int state[25] = { 0 };

    for(int i = 0; i < 25; i++){
        char c;
        std::cin >> c;
        if( c == '#' )
            state[i] = 1;
    }
    int br = bioRating(state);
    record[br] = 0;

    do{
        br = next(state);
        iteration++;
        
        if( record.count(br) != 0 )
            break;
        record[br] = iteration;
    }while( true );

    //br
    std::cout << br << std::endl;

    // std::cout << std::endl;
    // for(int j = 0; j < 5; j++){
    //     for(int i = 0; i < 5; i++){
    //         std::cout << adj(state, 5 * j + i) ;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << bioRating(state) << std::endl;
}