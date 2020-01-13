
#include <iostream>
#include <map>
#include <bitset>
#include <assert.h>
#include <vector>


constexpr int N = 5;
constexpr int N2 = N * N;
constexpr int S_LAST_ROW = N * (N - 1);
constexpr int MIDDLE = N * (N/2) + (N / 2);


typedef std::bitset<N2> Floor;
typedef std::vector< Floor > State;



int topLevel(State &st){
    return st.size() / 2 - 1;
}

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

int levelOf(int index){
    //(0, 1) -> (-1, 1)
    int s = 2 * (index % 2) - 1;
    return (index / 2) * s;
}

// int bioRating(State st){
//     return 0;
//     // return st.to_ulong();
// }

bool hasLevel(State &st, int lvl){
    return indexOf(lvl) < st.size();    
}

// 0 <= i < N2
int bugAt(State &st, int i, int lvl){
    int floor = indexOf(lvl);
    if( floor >= st.size() ) //empty floor
        return 0;

    Floor f = st[floor];
    return f[i];
}

void setAt(State &st, int i, int lvl, int value){    

    int floor = indexOf(lvl);
    while( floor >= st.size() ){
        st.push_back(Floor()); //-
        st.push_back(Floor()); //+
    }

    st[floor].set(i, value);
}

void print(State &st){
    int t = topLevel(st);
    for( int l = -t; l <= t; l++){
        std::cout << "Level " << l << ": " << std::endl;
        for(int i = 0; i < N2; i++){
            if( bugAt(st, i, l) )
                std::cout << "#";
            else
                std::cout << ".";
            if( i % N == N - 1 )
                std::cout << std::endl;
        }
        std::cout << std::endl;
           
    }
}

int adjacent(State &state, int i, int lvl){
    int adj = 0;
    
    //u
    if( i < N ){ //First row
        //Check the bottom lvl -1
        adj += bugAt(state, MIDDLE - N, lvl - 1);
    }else if( i == MIDDLE + N){ //bottom row of superior level
        for(int c = 0; c < N; c++){
            adj += bugAt(state, S_LAST_ROW + c, lvl + 1);
        }
    }else{
        adj += bugAt(state, i - N, lvl);
    }
    //d
    if( i >= S_LAST_ROW ){
        //Check the bottom lvl -1
        adj += bugAt(state, MIDDLE + N, lvl - 1);
    }else if( i == MIDDLE - N){ //bottom row of superior level
        for(int c = 0; c < N; c++){
            adj += bugAt(state, c, lvl + 1);
        }
    }else{
        adj += bugAt(state, i + N, lvl);
    }
    //l
    if( i % N == 0 ){
        adj += bugAt(state, MIDDLE - 1, lvl - 1);
    }else if( i == MIDDLE + 1){
        for(int r = N - 1; r < N2; r += N){
            adj += bugAt(state, r, lvl + 1);
        }
    }else{
        adj += bugAt(state, i - 1, lvl);
    }
    //r
    if( i % N == N - 1){
        adj += bugAt(state, MIDDLE + 1, lvl - 1);
    }else if( i == MIDDLE - 1){
        for(int r = 0; r < N2; r += N){
            adj += bugAt(state, r, lvl + 1);
        }
    }else{
        adj += bugAt(state, i + 1, lvl);
    }

    return adj;
}

void next(State &state){

    // std::vector < int[N2] > adj(state.size() + 2);

    // for( int k = 0; k < adj.size(); k++){
    //     int lvl = levelOf(k);
    //     for(int i = 0; i < N2; i++){
    //         if( i == MIDDLE )
    //             continue;
    //         adj[k][i] = adjacent(state, i, lvl);
    //     }
    // }

    State tmp;
    int t = topLevel(state);
    for( int l = -t; l <= t; l++){
        for(int i = 0; i < N2; i++)
            setAt(tmp, i, l, bugAt(state, i, l) );
    }

    // print(tmp);

    // unsigned int count = 0;
    for( int l = -t - 1; l <= t + 1; l++){
        for(int i = 0; i < N2; i++){
            if( i == MIDDLE )
                continue;

            int a = adjacent(tmp, i, l);

            if( bugAt(tmp, i, l) == 1 && a != 1 ){
                setAt(state, i, l, 0);
                continue;
            }
            
            if( bugAt(tmp, i, l) == 0 && (a == 1 || a == 2) ){
                setAt(state, i, l, 1);
                // count++;
            }
        }
    }

    // return count;
    // State nState;
    
    // //For all the used levels

    // //Advance
    // for(int i = 0; i < N2; i++){
    //     if( state[i] == 1 && adj[i] != 1 ){
    //         state[i] = 0;
    //         continue;
    //     }
    //     if( state[i] == 0 && (adj[i] == 1 || adj[i] == 2) )
    //         state[i] = 1;
    // }

    // return bioRating(state);
}

unsigned int countBugs(State &st){
    int t = topLevel(st);
    unsigned int count = 0;
    for( int l = -t; l <= t; l++){        
        for(int i = 0; i < N2; i++){
            if( i == MIDDLE )
                continue;

            if( bugAt(st, i, l) )
                count++;            
        }        
    }
    return count;
}


int main(){
    std::map<int, int> record;
    int iteration = 0;

    State state;

    for(int i = 0; i < N2; i++){
        char c;
        std::cin >> c;
        if( c == '#' )
            setAt(state, i, 0, 1);
            //state[i] = 1;
    }
    //std::cout<< MIDDLE << std::endl;
    //print(state) ;
    //std::cout << " ============================= "<< std::endl;
    
    for( int i = 0; i < 200; i++){
        next(state);
    }

    //print(state) ;
    std::cout << countBugs(state) << std::endl;

    // do{
    //     br = next(state);
    //     iteration++;
        
    //     if( record.count(br) != 0 )
    //         break;
    //     record[br] = iteration;
    // }while( true );

    // // //br
    // std::cout << br << std::endl;

    // std::cout << std::endl;

    // for(int j = 0; j < 5; j++){
    //     for(int i = 0; i < 5; i++){
    //         std::cout << adjacent(state, 5 * j + i) ;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << bioRating(state) << std::endl;
}