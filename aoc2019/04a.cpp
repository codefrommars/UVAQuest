#include <string>
#include <iostream>

bool checkNumber(int k){
    std::string str = std::to_string(k);

    bool twoSame = false;

    for( int i = 0; i < str.size() - 1; i++ ){
        
        if( str[i] == str[i + 1] )
            twoSame = true;

        if( str[i] > str[i + 1] )
            return false;
    }

    return twoSame;
}

int main(){
    int min = 265275;
    int max = 781584;

    int count = 0;
    for( int i = min; i <= max; i++ )
        if( checkNumber(i) )
            count++;
    
    std::cout << count << std::endl;

    return 0;
}