#include <iostream>

#define MAX (1000000000 / 5)

unsigned int table[MAX + 1];

unsigned int computeZ(int N){
    unsigned int z = 0;        

    do{
        N = N / 5;
        z += N;            
    }while( N > 0 );

    return z;
}

int main(){

    
    for( int i = 0; i <= MAX; i++ ){
        
    }
    // int T = 0;
    // std::cin >> T;   
    
    // while( T > 0 ){
    //     int N= 0;
        
    //     std::cin >> N;

    //     unsigned int z = 0;        

    //     do{
    //         N = N / 5;
    //         z += N;            
    //     }while( N > 0 );

    //     std::cout << table[T] << std::endl;
    //     T--;
    // }

    return 0;
}
