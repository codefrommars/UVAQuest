#include <iostream>
#include <algorithm>

#define MAX 30
int paths[MAX][MAX];
int N;


void clear_paths() {
    for( int i = 0; i < MAX; i++ )
        for( int j = 0; j < MAX; j++ )
            paths[i][j] = 0;
}


void compute_paths() {
    for( int k = 0; k < N; k++ )
        for( int i = 0; i < N; i++ )
            for( int j = 0; j < N; j++ )
                paths[i][j] += paths[i][k] * paths[k][j];
    
    //Remove cycles
    for( int k = 0; k < N; k++ )
        if( paths[k][k] != 0 )            
            for( int i = 0; i < N; i++ )
                for( int j = 0; j < N; j++ )
                    if( paths[i][k] != 0 && paths[k][j] != 0 )                    
                        paths[i][j] = -1;

    for( int i = 0 ; i < N; i++ ){
        for( int j = 0 ; j < N; j++ ){
            std::cout << paths[i][j];
            if( j != N -1 ) 
                std::cout<< ' ';
        }
        std::cout << std::endl;
    }
}


int main() {
    int st = 0, a, b;    
    clear_paths();
    int city = 0;
    while( std::cin >> st ) {
        N = -1;

        //clear indices
        for(int i = 0; i < st; i++){
            std::cin >> a >> b;
            paths[a][b] += 1; //In case they have "a -> b, a -> b, a -> b"
            N = std::max( std::max( N, a ), b );
        }
        N++;
    	
        std::printf("matrix for city %i\n", city);
        compute_paths();
        clear_paths();
        city++;
    }

    return 0;
}