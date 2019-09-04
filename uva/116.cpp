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

int lexic_diff(int a, int b, int n){
	int d = 0;
	for( int j = n - 1; j >= 0; j--){
		if( a - b != 0 )
			d = a - b;

		a = minp[a][j];
		b = minp[b][j];
	}

	return d;
}

void print_mp(int m, int n){
	int mp = -1;

	for(int j = 1; j < n; j++){
		for(int i = 0; i < m; i++){
			mp = prev(i, -1, m);

			for( int r = 0; r <= 1; r++ ){
				int p = prev(i, r, m);
				if( c[p][j - 1] < c[mp][j - 1] ){
					mp = p;
				}else if( c[p][j - 1] == c[mp][j - 1] ){
					if( lexic_diff(p, mp, j) < 0 )
						mp = p;
				}
			}

			//update
			c[i][j] += c[mp][j - 1];
			minp[i][j] = mp;
		}
	}

	mp = 0;
	
	for( int i = 1; i < m; i++){
		if( c[i][n - 1] < c[mp][n - 1] )
			mp = i;
		else if( c[i][n - 1] == c[mp][n - 1] ){
			if( lexic_diff(i, mp, n) < 0 )
				mp = i;
		}
	}

	int cost = c[mp][n - 1];

	int path[100]; 
	for( int j = n - 1; j >= 0; j--){
		path[j] = mp;
		mp = minp[mp][j];
	}

	for( int j = 0; j < n; j++){
		std::printf("%i", path[j] + 1);
		if( j != n - 1)			// Without this you'll get a presentation error :(
			std::printf(" "); 	//
	}
	
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
