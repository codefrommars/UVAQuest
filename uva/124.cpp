#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define LEN ('z' - 'a' + 1)
#define MAX 20

char vars[MAX];
int index[LEN];

int s[MAX];
int t[MAX];
int less[MAX][MAX];
int opt[MAX][MAX];
int copt[MAX];
int lock[MAX];
int comb[MAX];

int n;

void print_comb(){
    for( int i = 0; i < n; i++ )
        std::printf("%c", vars[comb[i]]);
    
    std::printf("\n");
}

void combine(int k) {

    if( k == n ){
        print_comb();
        return;
    }

    for( int i = 0; i < copt[k]; i++){        
        int v = opt[k][i];
        if( lock[v] > 0 )
            continue;
        // std::printf("in %c\n", vars[v]);
        lock[v]++; //block
        for( int j = 0; j < n; j++){
            if( less[j][v] )
                lock[j]++;
            // std::printf("%i,", lock[j]);
        }
        // std::printf("\n");

        comb[k] = v;
        combine(k + 1);
        
        // std::printf("out %c\n", vars[v]);
        lock[v]--; //release
        for( int j = 0; j < n; j++){
             if( less[j][v] )
                lock[j]--;
            // std::printf("%i,", lock[j]);
        }
        // std::printf("\n");
    }
}


void list_options() {
    // transitive closure
    for( int k = 0; k < n; k++){
        for( int i = 0; i < n; i++ ){
            if( !less[i][k] )
                continue;

            for( int j = 0; j < n; j++ ){
                if( less[k][j] )
                    less[i][j] = 1;
            }
        }
    }

    //compute s, t
    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < n; j++ ){
            t[i] += less[i][j];
            s[j] += less[i][j];
            // std::printf("%i ", less[i][j]);
        }
        // std::printf("\n");
    }

    //add options
    for( int v = 0; v < n; v++){
        // std::printf("%c : (%i, %i) \n", vars[v], s[v], n - t[v] - 1);
        for( int i = s[v]; i < n - t[v]; i++){
            opt[i][ copt[i] ] = v;
            copt[i] ++;
        }
    }
    // combine recursively
    combine(0);
}


int main() {

    std::string line;
    bool first = false;

    while( std::getline (std::cin,line ) ) {
        if( first )
            std::printf("\n");
        
        //clear indices
        for(int i = 0; i < LEN; i++){
            index[i] = -1;
        }

        first = true;
        //First line
        //n = 0;
        std::stringstream str = std::stringstream(line);
              
        while( str >> vars[n] ){
            index[ (int)vars[n] - 'a' ] = 1;
           // n++;
        }

        //order
        n = 0;
        for(int i = 0; i < LEN; i++){
            if( index[i] == -1 )
                continue;
            vars[ n ] = i + 'a';
            index[i] = n;
            // std::printf("%c : index(%i) = %i) \n", vars[n], i, n);
            n++; 
        }

        for(int i = 0; i < n; i++){
            s[i] = 0;
            t[i] = 0;
            copt[i] = 0;
            lock[i] = 0;
            for(int j = 0; j < n; j++){
                less[i][j] = 0;
                opt[i][j] = -1;
            }
        }
        

        //Second line
        std::getline(std::cin,line );
        str = std::stringstream(line);
        //std::cout << line << std::endl;
        char x, y;
        while( str >> x >> y ){
            int ix = index[x - 'a'];
            int iy = index[y - 'a'];

            less[ix][iy] = true;
            //  std::printf("%c < %c\n", vars[ix], vars[iy]);
        }
        
        list_options();
    }

    return 0;
}