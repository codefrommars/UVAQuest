#include <iostream>
#include <cstring>

#define MAX_SIZE    1000000

bool is_all_nine(char * str, int len){
    for( int i = 0; i < len; i++)
        if( str[i] != '9' )
            return false;

    return true;
}

void next_palindrome( char* str, int len ) {
    
    if( is_all_nine(str, len) ){
        std::cout << '1';

        for( int i = 0; i < len - 1; i++)
            std::cout << '0';        
        
        std::cout << '1';

        return;
    }

    int s = len / 2;

    int even = 1 - (len % 2);
    int r = s;
    int l = s - even;

    int inc = 0;    

    bool pal = true;

    for(int i = 0; i <= l; i++ ){

        if( str[l - i] != str[r + i] )
            pal = false;

        if( str[l - i] > str[r + i] )//copy            
            break;        

        if( str[l - i] < str[r + i] ){//increment
            inc = 1;
            break;
        }
    }

    while( inc > 0 || pal ){
        int val = (str[l] - '0') + 1;
        str[l] = (val % 10) + '0';
        str[r] = str[l];
        l--;
        r++;

        inc = val / 10;
        pal = false;
    }
    
    while( l >= 0 ){
        str[r] = str[l];
        l--;
        r++;
    }

    for( int i = 0; i < len; i++){
        std::cout << str[i];
    }

}

int main(){

    char line[MAX_SIZE];    

    int cases = 0;
    std::cin >> cases;
    
first:
    while( cases > 0 ){
        
        scanf("%s", line);       
        
        next_palindrome(line, std::strlen(line));
        
        std::cout << std::endl;        

        cases--;
    }
    
    return 0;
}
