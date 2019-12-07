#include <iostream>

#define MAX 101

int g[MAX][MAX];

int max_path(int n, int s, int* m){
    int p = 0;
    int local_m = s;

    for( int j = 0; j < n; j++ ){
        if( g[s][j] == 0 )
            continue;

        int path_i = max_path(n, j, m) + 1;
        
        if( path_i > p ){
            p = path_i;
            local_m = *m;
        }else if( path_i == p && *m < local_m ){
            local_m = *m;
        }
    }

    *m = local_m;    
    return p;
}

int main() {

    int n;
    int s;
    int p, q;
    
    int m;
    int c = 0;
    while( std::cin >> n ){

        if( n == 0 )
            break;
        
        c++;

        std::cin >> s;
        s--;
        for( int i = 0; i < n; i++)
            for( int j = 0; j < n; j++)
                g[i][j] = 0;
        
        do {
            std::cin >> p;
            std::cin >> q;
            g[p-1][q-1] = 1;
        }while( p != 0 && q != 0);

        int l = max_path(n, s, &m);
        std::printf("Case %i: The longest path from %i has length %i, finishing at %i.\n\n", c, s + 1, l, m + 1);
    }

    return 0;
}