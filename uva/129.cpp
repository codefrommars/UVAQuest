#include <iostream>

#define MAX 80

#define LETTER(x)   (x + 'A')

char seq[MAX + 1];
int currseq = 0;

bool print_seq(int len){
    
    int gr = 0;
    int i = 0;
    do{
        std::printf("%c", seq[i]);
        i++;
        if( i % 4 == 0 ){ //new group
            gr++;
            if( i >= len )
                break;
            if( gr % 16 == 0 )
                std::printf("\n");
            else
                std::printf(" ");
        }
    }while( i < len );

    std::printf("\n%i\n", len);
    
    return true;
}

bool equal_sub(const char* p, const char* q, int sslen){
    for( int i = 0; i < sslen; i++ ){
        if( *p != *q )
            return false;
        p++;
        q++;        
    }

    return true;
}

bool can_place(char c, int len){
    
    seq[len] = c;    
    int ss = 1;
    int p = len + 1 - ss, q = len + 1 - 2 * ss;

    while( q >= 0 ){
        if( equal_sub(&seq[p], &seq[q], ss) )
            return false;
        ss++;
        p = len + 1- ss;
        q = len + 1- 2 * ss;
    }

    return true;
}

int find_seq(int len, int n, int L) {    


    for( int c = 0; c < L; c++ ){
        char letter = LETTER(c);
        if( can_place(letter, len) ){
            currseq++;
            //print_seq(currseq);

            if( currseq == n )
                return len + 1;

            int f = find_seq(len + 1, n, L);
            if( f != -1 )
                return f;

        }
    }
    return -1;
}





int main() {


    int n, L;
    while( std::scanf("%i %i", &n, &L) != EOF ){
        if( n == 0 && L == 0 )
            break;

        currseq = 0;        
        int len = find_seq(0, n, L);        
        print_seq(len);        
    }



    return 0;
}