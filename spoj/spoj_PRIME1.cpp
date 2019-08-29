#include <iostream>

bool isPrime(int num){
    if( num == 1 )
        return false;

    for( int i = 2; i * i <= num; i++)
        if( num % i == 0 )
            return false;
    
    return true;
}

int main(){
    int cases = 0;
    std::cin >> cases;
    
    for( int t = 0; t < cases; t++ ){
        int m= 0, n = 0;
        std::cin >> m;
        std::cin >> n;

        for( int i = m; i <= n; i++)
            if( isPrime(i) )
                std::cout << i << std::endl;
         std::cout << std::endl ;
    }

    return 0;
}
