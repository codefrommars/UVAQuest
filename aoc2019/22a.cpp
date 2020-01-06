#include <iostream>
#include <algorithm>
#include <string>

constexpr int N = 10007;
// constexpr int N = 10;

int deck[N];
int tmp[N];

void init(){
    for( int i = 0; i < N; i++)
        deck[i] = i;
}

void cut(int c){
    if( c < 0 )
        c += N;

    std::copy(deck, deck + c + 1, tmp + N - c);
    std::copy(deck + c, deck + N, tmp);
    
    std::copy(tmp, tmp + N, deck);
}

void dealINS(){
    for( int i = 0; i < N; i++)
        tmp[i] = deck[N - 1 - i];
    
    std::copy(tmp, tmp + N, deck);
}

void dealWI(int inc){
    for(int i = 0; i < N; i++)
        tmp[ (inc * i) % N ] = deck[i];
    
    std::copy(tmp, tmp + N, deck);
}

void show(){
    for( int i = 0; i < N; i++)
       std::cout << deck[i] << " ";
    std::cout << std::endl;
}

int main(){
    
    init();

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
    
    for( int i = 0; i < N; i++){
        if( deck[i] == 2019 ){
            std::cout << i << std::endl;
            break;
        }
    }
    // show();
}