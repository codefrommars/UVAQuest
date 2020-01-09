#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

inline __int64 pmod(__int64 value, __int64 mod){
    value = value % mod;
    
    if( value < 0 )
        value += mod;

    return value;
}

inline __int64 mult_mod(__int64 a, __int64 b, __int64 mod){
    __int64 p = 0;


    while( b > 0 ){
        if( b % 2 == 1 )
            p = pmod(p + a, mod);
        a = pmod(a * 2, mod);
        b = b / 2; 
    }

    return p;
}

__int64 big_pow(__int64 a, __int64 n, __int64 m){
    if( n == 0 )
        return 1;
    if( n == 1 )
        return a;

    if( n % 2 == 0 ){
        __int64 p = big_pow(a, n >> 1, m);
        return mult_mod( p , p, m);
    }

    __int64 p = big_pow(a, (n - 1) >> 1, m);
    return mult_mod( mult_mod(a , p, m) , p, m);
}

void comp( __int64 &a, __int64 &b, __int64 c, __int64 d, __int64 m){
    __int64 at = mult_mod(a , c, m);
    __int64 bt =  pmod( mult_mod(b , c, m) + d, m);

    a = at;
    b = bt;
}

void fn_pow( __int64 &a, __int64 &b, __int64 m, __int64 n){

    if( n == 1 )
        return;

    if( n % 2 == 0 ){
        comp(a, b, a, b, m);        
        fn_pow( a, b, m, n >> 1);
    }else{        
        __int64 a1 = a;
        __int64 b1 = b;
        comp(a, b, a, b, m);
        fn_pow( a, b, m, (n - 1) >> 1);
        comp(a1, b1, a, b, m);
        a = a1;
        b = b1;
    }
}



int main(){
    
    std::string word;    
    constexpr __int64 N = 119315717514047;
    constexpr __int64 SHUFFLES = 101741582076661;
       
    __int64 q = 2020;

    __int64 a = 1;
    __int64 b = 0;

    while(std::cin >> word){
        if( word.compare("deal") == 0 ){
            std::cin >> word ; 
            if( word.compare("with") == 0 ){
                std::cin >> word ; // increment
                int inc;
                std::cin >> inc;                
                a = mult_mod(a , inc, N);
                b = mult_mod(b , inc, N);
                continue;
            }

            if( word.compare("into") == 0 ){
                std::cin >> word ; // new
                std::cin >> word ; // stack                
                a = pmod(-a, N);
                b = pmod(-b - 1, N);
                continue;
            }
        }

        if( word.compare("cut") == 0 ){
            int n;
            std::cin >> n;            
            b = pmod(b - n, N);
        }
    }

    fn_pow(a, b, N, SHUFFLES);
    //Invert
    fn_pow(a, b, N, N - 2);

    __int64 iq = pmod( mult_mod(a , q, N) + b, N );
    
    std::cout << iq << std::endl;
}