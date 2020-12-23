#include <iostream>
#include <vector>

std::vector<int> start = {4,7,6,1,3,8,2,5,9};
std::vector<int> next; // -> next of cup c in the list 

void setup(int max) {
    next = std::vector<int>(max + 1, 0);
    for( int p = 0; p < next.size(); p++)
        next[p] = p + 1;
    
    for( int p = 0; p < start.size() - 1; p++)
        next[start[p]] = start[p + 1];
    
    next[0] = start[0];//0 is the list header.

    int maxStartValue = start[ start.size() - 1];
    next[maxStartValue] = start.size() + 1;

    if( max == start.size())
        max = maxStartValue;
    
    next[max] = start[0];
}

void run(int iterations){
    int curr = next[0];
    for(int i = 0; i < iterations; i++){
        int e1 = next[curr];
        int e2 = next[e1];
        int e3 = next[e2];
        
        next[curr] = next[e3];
        int d = curr;
        do{
            d = ( d == 1 ) ? next.size() - 1 : d - 1;
        }while( d == e1 || d == e2 || d == e3 );
        next[e3] = next[d];
        next[d] = e1;
        curr = next[curr];
    }
}

void part1() {
    setup(9);
    run(100);
    for( int i = next[1]; i != 1; i = next[i] )
        std::cout << i;
    std::cout << std::endl;
}

void part2() {
    setup(1000000);
    run(10000000);
    std::cout << (long)next[1] * next[next[1]] << std::endl;
}

int main() {
    part2();
}