#include <iostream>
#include <algorithm>

#define MAX 30
int count[MAX][MAX];
int paths[MAX][MAX];
bool visited[MAX];
int N;


void clear_counts() {
    for( int i = 0; i < MAX; i++ ){
        visited[i] = false;
        for( int j = 0; j < MAX; j++ ){
            count[i][j]= -2;
        }
    }
}

void clear_paths() {
    for( int i = 0; i < MAX; i++ ){
        for( int j = 0; j < MAX; j++ ){
            paths[i][j] = 0;
        }
    }
}

int countp(int i, int j){

    // if( i == j ){
    //     if( visited[i] )
    //         return -1;
    //     return 0;
    // }

    if( count[i][j] != -2 )
        return count[i][j];
    
    int pk = 0;
    int sum = 0;
    for( int k = 0; k < N; k++ ){
        if( paths[i][k] == 0)
            continue;
        // std::cout << i <<" -> " << k << std::endl;
        if( visited[k] ){
            //cycle
            sum = -1;
            break;
        }

        
        if( k == j ){
            pk = 1;
        }else{
            visited[k] = true;
            pk = countp(k, j);
            visited[k] = false;
        }
        
        if( pk == -1 ){
            sum = -1;
            break;
        }
        sum += pk;
    }
    count[i][j] = sum;
    return sum;
}

// void compute_paths(){
//     for( int i = 0 ; i < N; i++ ){
//         visited[i] = true;
//         for( int j = 0 ; j < N; j++ ){
//             std::cout << countp(i, j);
//             if( j != N -1 ) 
//                 std::cout<< ' ';
//         }
//         visited[i] = false;
//         std::cout << std::endl;
//     }
// }

void compute_paths() {

    // for( int k = 0; k < N; k++ ){
    //     for( int i = 0; i < N; i++ ){
    //         for( int j = 0; j < N; j++ ){
    //             paths[i][j] += paths[i][k] * paths[k][j];
    //         }
    //     }
    // }

    //Remove cycles
    // for( int k = 0; k < N; k++ )
    //     for( int i = 0; i < N; i++ ){
    //         if( paths[i][k] == 0 || paths[k][i] == 0 )
    //             continue;

    //         for( int j = 0; j < N; j++ ){

    //             if(  paths[i][j] != 0){
    //                 paths[i][j] = -1;                    
    //             }

    //             if(  paths[k][j] != 0){
    //                 paths[k][j] = -1;                    
    //             }
    //         }
    //     }

    for( int k = 0; k < N; k++ ){
        for( int i = 0; i < N; i++ ){
            if( paths[i][k] == 0 )
                continue;
            for( int j = 0; j < N; j++ ){
                if( paths[k][j] == 0 )
                    continue;
                //i connected to j through k
                int count = 0;
                if( paths[i][k] == -1 )
                    count = -1;
                else if( paths[k][j] = -1 )
                    count = -1;
                else if( i == j ){
                    count = -1;
                }else
                    count = paths[i][j] + paths[i][k] * paths[k][j];
                
                // if( count == -1 ){
                //     //paths[i][k] = -1;
                //     //paths[k][j] = -1;
                // }
                //if( i == 3 && j == 4 )
                std::cout << i << " -> " << k << " -> " << j << std::endl;
                paths[i][j] = count;
                //paths[i][j] += paths[i][k] * paths[k][j];
            }
        }
    }

    //Cancel cycles
    // for( int i = 0; i < N; i++ )
    //     if( paths[i][i] != 0 )
    //         paths[i][i] = -1;

    // for( int k = 0; k < N; k++ ){
    //     for( int i = 0; i < N; i++ ){
    //         if( /*paths[i][i] == 0 || paths[i][k] == 0*/ paths[i][k] != -1 )
    //             continue;

    //         for( int j = 0; j < N; j++ ){
    //             if( paths[k][j] == 0 )
    //                 continue;

    //             paths[i][j] = -1;
    //         }
    //     }
    // }

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
    clear_counts();
    clear_paths();
    int city = 0;
    while( std::cin >> st ) {
        // if( first )
        //     std::printf("\n");
        N = -1;
        //clear indices
        for(int i = 0; i < st; i++){
            std::cin >> a >> b;
            paths[a][b] = 1;
            N = std::max( std::max( N, a ), b );
        }
        N++;
    	
        std::printf("matrix for city %i\n", city);
        compute_paths();

        clear_counts();
        clear_paths();
        city++;
    }

    return 0;
}