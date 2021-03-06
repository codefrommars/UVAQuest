
#include <iostream>
#include <map>
#include <bitset>

constexpr int N = 5;
constexpr int N2 = N * N;

typedef std::bitset<N2> State;

int bioRating(State st){
    return st.to_ulong();
}

int bugAt(State st, int i){
    if( i < 0 || i >= 25 )
        return 0;
    return st[i];
}

int adjacent(State state, int i){
    //up and down, no problem
    int u = bugAt(state, i - N);
    int d = bugAt(state, i + N);

    int row = i / N;
    int l = 0;
    //left and right only if remains in same row
    if( (i - 1) / N == row )
        l = bugAt(state, i - 1);
    
    int r = 0;
    if( (i + 1) / N == row )
        r = bugAt(state, i + 1);

    return u + d + l + r;
}

int adj[25];

int next(State &state){
    for(int i = 0; i < N2; i++)
        adj[i] = adjacent(state, i);
    
    for(int i = 0; i < N2; i++){
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

    State state;

    for(int i = 0; i < N2; i++){
        char c;
        std::cin >> c;
        if( c == '#' )
            state[i] = 1;
    }
    int br = bioRating(state);

    do{
        br = next(state);
        iteration++;
        
        if( record.count(br) != 0 )
            break;
        record[br] = iteration;
    }while( true );

    std::cout << br << std::endl;
}