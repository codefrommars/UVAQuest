#include <iostream>

bool isValid1(int min, int max, char c, char* str){
    int count = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if( str[i] == c )
            count++;
        if( count > max )
            return false;
    }

    return count >= min;
}

int part1() {
    int min, max;
    char c;
    char str[100];
    int valid = 0;

    while( scanf("%i-%i %c: %s\n", &min, &max, &c, &str[0]) > 0 ) {
        if(isValid1(min, max, c, str))
            valid ++;
    }

    std::cout << valid << std::endl;

    return 0;
}

bool isValid2(int p1, int p2, char c, char* str){
    return (str[p1 - 1] == c) ^ (str[p2 - 1] == c);
}

int part2() {
    int min, max;
    char c;
    char str[100];
    int valid = 0;
    
    while( scanf("%i-%i %c: %s\n", &min, &max, &c, &str[0]) > 0 ) {
        if(isValid2(min, max, c, str))
            valid ++;
    }

    std::cout << valid << std::endl;

    return 0;
}

int main() {
    return part2();
}