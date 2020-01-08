#include <iostream>
#include <algorithm>
#include <string>

constexpr __int64 N = 10007;

__int64 p = 2019;

// void cut(int c){
//     p = (p - c) % N;
// }

// void dealINS(){
//     //p = N - 1 - p;
//     p = (N - 1 - p) % N;
// }

// void dealWI(int inc){
//     p = (inc * p) % N;
// }


// __int64 egcd(__int64 a, __int64 b, __int64 &x, __int64& y){
//     if( a == 0 ){
//         x = 0; 
//         y = 1;
//         return b;
//     }

//     __int64 x1, y1;
//     __int64 d = egcd( b % a, a, x1, y1);
//     x = y1 - (b / a) * x1;
//     y = x1;
//     return d;
// }

int main(){
    
    std::string word;
    constexpr __int64 N = 10007;

    __int64 p = 2019;

    __int64 a = 1;
    __int64 b = 0;

    __int64 x = 1;
    __int64 y = 0;



    while(std::cin >> word){
        if( word.compare("deal") == 0 ){
            std::cin >> word ; 
            if( word.compare("with") == 0 ){
                std::cin >> word ; // increment
                int inc;
                std::cin >> inc;
                // dealWI(inc);                
                a = (a * inc) % N;
                b = (b * inc) % N;
                continue;
            }

            if( word.compare("into") == 0 ){
                std::cin >> word ; // new
                std::cin >> word ; // stack
                // dealINS();
                a = -a;
                b = (-b - 1) % N;
                continue;
            }
        }

        if( word.compare("cut") == 0 ){
            int n;
            std::cin >> n;
            // cut(n);
            b = (b - n) % N;
        }
    }

    //std::cout << a << " " <<  b << std::endl;

    __int64 r = (2019 * a + b) % N;
    if( r < 0 )
        r += N;

    std::cout << r << std::endl;

    //std::cout << p << std::endl;
}