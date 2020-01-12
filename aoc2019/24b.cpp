
#include <iostream>
#include <map>
#include <bitset>
#include <vector>


constexpr int N = 5;
constexpr int N2 = N * N;

typedef std::bitset<N2> Floor;
typedef std::vector< Floor > State;

int sgn(int n){
    return (n < 0) ? -1 : 1 ;
}

//- + - + - + - + - + - +
//0 0 1 1 2 2 3 3 4 4 5 5 
int indexOf(int lvl){
    //(-1, 1) -> +1, ÷2 (0, 1)
    int s = (sgn(lvl) + 1) / 2;
    return 2 * std::abs(lvl) + s;
}

// int levelOf(int index){
//     //(0, 1) -> (-1, 1)
//     int s = 2 * (index % 2) - 1;
//     return (index / 2) * s;
// }

int bioRating(State st){
    return 0;
    // return st.to_ulong();
}

Floor& floorAt(State &st, int lvl){
   
}

int bugAt(State st, int i, int lvl){
    int floor = indexOf(lvl);
    if( floor >= st.size() ) //empty floor
        return 0;

    Floor f = st[floor];
    
    // if( i < 0 || i >= 25 )
    //     return 0;
    // return st[i];
    return 0;
}

int adjacent(State state, int i, int lvl){
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

int next(State &state){

    State nState;
    
    //For all the used levels

    //Advance
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

    // //br
    std::cout << br << std::endl;

    // std::cout << std::endl;

    // for(int j = 0; j < 5; j++){
    //     for(int i = 0; i < 5; i++){
    //         std::cout << adjacent(state, 5 * j + i) ;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << bioRating(state) << std::endl;
}