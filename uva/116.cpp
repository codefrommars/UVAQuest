#include <cstdio>
#include <algorithm>

int c[10][100];

int minc[10][100];

int minp[100];

inline int prev(int i, int j, int r, int m){
	int s = p + r;
	if( s < 0 )
		return m + s;
	return s;
}

void print_mp(int m, int n){
	minp[0] = 0;
	minc[0][0] = c[minp[0]][0];
	
	for( int i = 1; i < m; i++){
		minc[i][0] = c[i][0];
		if( c[i][0] < minc[minp[0]][0] ){
			minp[0] = i;
		}
	}
	
	//std::printf("%i", p + 1);
	
	for(int j = 1; j < n; j++){
		for(int i = 0; i < m; i++){
			
			for( int r = -1; r <= 1; r++ ){
				int q = index(p, r, m);
				int cr = minc[q][j - 1] + c[i][j];
				
			}
		}
	}
}

int main(){
	int m, n;
	
	while( std::scanf("%i %i", &m, &n) != EOF ){		
		for(int i = 0; i < m; i++)
			for(int j = 0; j < m; j++)
				std::scanf("%i", &c[i][j]);
		
		print_mp(m, n);
	}
}
