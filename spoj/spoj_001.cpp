#include <iostream>

int main(){
    int num = 0;
    
    while( std::cin >> num ){
        
        if( num == 42 )
            break;

        std::cout << num << std::endl;
    }
    
    return 0;
}