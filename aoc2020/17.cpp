#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <vector>

int constexpr N = 30;
using Coord = unsigned int; 
// idx = a0 + (a1 + (a2 + a3 * N) * N) * N
Coord idx(std::vector<int> a, int dim, int n = N){
    int coord = 0;
    for( int i = dim - 1; i >= 0; i--){
        int val = i < a.size() ? a[i] : 0;
        coord = (val + (n / 2)) + coord * n;
    }
    return coord;
}
// crd(idx) = ai
int crd(Coord idx, int i, int n ){
    idx /= std::pow(n, i);
    return ( idx % n) - (n / 2);
}

std::unordered_set<Coord> step( const std::unordered_set<Coord>& state, int dim ) {
    std::unordered_set<Coord> next;
    std::unordered_map<Coord, int> nCounter;
    //Compute the counters of the cells close to an active cell
    for( Coord pos : state ){
        if( nCounter.count(pos) == 0 )
            nCounter[pos] = 0;

        int k = std::pow(3, dim);
        for( Coord i = 0; i < k; i++ ) {
            if(  i == k / 2 ) // skip the (0, 0, ... ) neighbor
                continue; 
            Coord c = 0;
            for( int d = dim - 1; d >= 0; d--)
                c = (crd(pos, d, N) + crd(i, d, 3) + (N / 2)) + c * N;
            nCounter[ c ] ++;
        }
    }
    //Do the Active/Inactive logic based on the counters, only write the active in the map
    for( auto c : nCounter )
        if( state.count(c.first) == 1 ) { //Active
            if( c.second == 2 || c.second == 3 )
                next.insert(c.first);
        }else {
            if( c.second == 3 )
                next.insert(c.first);
        }
    return next;
}

void run(int dim) {
    std::unordered_set<Coord> state; int y = 0;
    for(std::string line; std::cin >> line; y++)
        for( int x = 0 ; x < line.size(); x++ )
            if( line[x] == '#')
                state.insert( idx({x, y}, dim) );

    for(int i = 0; i < 6; i++)
        state = step(state, dim);

    std::cout << state.size() << std::endl;
}

void part1() {
    run(3);
}

void part2(){
    run(4);
}

int main() {
    part2();
}