#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define LEN ('z' - 'a')
#define MAX 20

char vars[MAX];
int index[LEN];

int s[MAX];
int t[MAX];
int less[MAX][MAX];
int opt[MAX][MAX];
int copt[MAX];
bool lock[MAX];
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
        if( lock[v] )
            continue;
        lock[v] = true; //block
        comb[k] = v;
        combine(k + 1);
        lock[v] = false; //release
    }
}


void force(int x, int y){
    if( s[y] == 0 ){
        less[x][y] = 1;
        return;
    }

    for( int j = 0; j < n; j++ )
        if( less[y][j] )
            force(x, j);
}

void augment() {
    

    for( int v = 0; v < n; v++ )
        for( int j = 0; j < n; j++ ){
            if( less[v][j] )
                force(v, j);
        }
}


int main() {

    std::string line;

    while( std::getline (std::cin,line ) ) {
        //First line
        n = 0;
        std::stringstream str = std::stringstream(line);
              
        while( str >> vars[n] ){
            index[ (int)vars[n] - 'a' ] = n;
            n++;
        }

        for(int i = 0; i < n; i++){
            s[i] = 0;
            t[i] = 0;
            copt[i] = 0;
            for(int j = 0; j < n; j++){
                less[i][j] = 0;
                opt[i][j] = -1;
            }
        }
        

        //Second line
        std::getline (std::cin,line );
        str = std::stringstream(line);
        //std::cout << line << std::endl;
        char x, y;
        while( str >> x >> y ){
            int ix = index[x - 'a'];
            int iy = index[y - 'a'];

            less[ix][iy] = true;
            s[ix]++;
            t[iy]++;
        }
        
        //augment less


        std::printf("\n");
    }

    return 0;
}