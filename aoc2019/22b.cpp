#include <iostream>
#include <algorithm>
#include <string>

constexpr __int64 N = 10;

__int64 p = 3;

void cut(int c){

    if( c < 0 )
        c += N;
    if( p < c )
        
    // p = (p - c) % N;
}

void dealINS(){
    p = N - 1 - p;
}

void dealWI(int inc){
    p = (inc * p) % N;
}

int main(){

    // cut(-4);

    std::string word;
    while(std::cin >> word){
        if( word.compare("deal") == 0 ){
            std::cin >> word ; 
            if( word.compare("with") == 0 ){
                std::cin >> word ; // increment
                int inc;
                std::cin >> inc;
                dealWI(inc);
                continue;
            }

            if( word.compare("into") == 0 ){
                std::cin >> word ; // new
                std::cin >> word ; // stack
                dealINS();
                continue;
            }
        }

        if( word.compare("cut") == 0 ){
            int n;
            std::cin >> n;
            cut(n);
        }
    }

    std::cout << p << std::endl;
}