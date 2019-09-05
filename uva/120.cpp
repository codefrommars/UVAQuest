#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <map>

void swap(int* stack, int i, int j){
    int t = stack[i];
    stack[i] = stack[j];
    stack[j] = t;
}


bool test(int* stack, int n){
    for( int i = 1; i < n; i++ )
        if( stack[i - 1] > stack[i] )
            return false;
    return true;
}

void flip(int k, int* stack, int n){
    if( k == 0 )
        return;
    
    int i = 0;
    int j = k;
    while( i < j ){
        swap(stack, i, j);
        i++;
        j--;
    }

    std::printf("%i ", n - k);
}

int max(int* stack, int p){
    int m = p;
    while( p >= 0 ){
        if( stack[p] > stack[m] )
            m = p;
        p--;
    }
    return m;
}

void order(int* stack, int n){
    if( test(stack, n) )
        return;
    //for( int i = 0; i < n; i++ )
    //    std::cout << stack[i] << std::endl;
    for( int i = n - 1; i > 0; i--) {
        int m = max(stack, i);
        
        if( m == i )
            continue;

        flip(m, stack, n);
            
        if( test(stack, n) )
            return;

        flip(i, stack, n);
        if( test(stack, n) )
            return;
    }
}

int main() {

    
    std::string line;
    int stack[30];
    while( std::getline (std::cin,line ) ) {
        std::cout << line << std::endl;

        int n = 0;

        std::stringstream str = std::stringstream(line);
              
        while( str >> stack[n] )
            n++;        

        order(stack, n);
        std::printf("%i\n", 0);
    }

    return 0;

}