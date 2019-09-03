#include <cstdio>
#include <algorithm>

int c[10][100];

int minp[10][100];

inline int prev(int i, int r, int m){
	int s = i + r;
	if( s < 0 )
		return m + s;
	return s % m;
}

void print_mp(int m, int n){

	// for( int i = 0; i < m; i++)
	// 	minp[i][0] = -1;
	int mp = -1;
	for(int j = 1; j < n; j++){
		for(int i = 0; i < m; i++){
			//int cij = c[i][j];
			mp = prev(i, -1, m);
			// int mc = c[mp][j - 1];

			for( int r = 0; r <= 1; r++ ){
				int p = prev(i, r, m);
				if( c[p][j - 1] < c[mp][j - 1] ){
					mp = p;
					// mc = c[p][j - 1];
				}else if( c[p][j - 1] == c[mp][j - 1] ){
					if( minp[p][j - 1] < minp[mp][j - 1] )
						mp = p; 
					//if( p < mp )
					//	mp = p;
				}
			}

			//update
			c[i][j] += c[mp][j - 1];
			minp[i][j] = mp;
		}
	}

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			std::printf("%i ", c[i][j]);
		std::printf("\n");
	}
	std::printf("\n");

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++)
			std::printf("%i ", minp[i][j]);
		std::printf("\n");
	}
	std::printf("\n");

	// int mc = c[0][n - 1];
	mp = minp[0][n - 1];
	
	for( int i = 1; i < m; i++)
		if( c[i][n - 1] < c[mp][n - 1] )
			mp = i;

	std::printf("%i\n", mp);
	int cost = c[mp][n - 1];

	int path[100]; 
	for( int j = n - 1; j >= 0; j--){
		path[j] = mp;
		mp = minp[mp][j];
	}

	for( int j = 0; j < n; j++)
		std::printf("%i ", path[j] + 1);
	
	std::printf("\n");
	
	std::printf("%i\n", cost);
	
}

int main(){
	int m, n;
	
	while( std::scanf("%i %i", &m, &n) != EOF ){		
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				std::scanf("%i", &c[i][j]);
		
		print_mp(m, n);
	}
}
