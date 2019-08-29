#include <cstdio>
#include <limits>

int S[100][100][100][100];

int main(){
	unsigned int n;
	
	std::setbuf(stdout, NULL);
	
	while(std::scanf("%i", &n) != EOF){
		int max = std::numeric_limits<int>::min();
		
		for(int i = 0; i < n; i++ )
			for(int j = 0; j < n; j++ ){
				std::scanf("%i", &S[i][j][0][0] );
				if ( S[i][j][0][0] > max )
					max = S[i][j][0][0];
			}
		
		for(int w = 0; w < n ; w++)
			for(int h = 0; h < n ; h++)
				for( int i = 0; i < n - h; i++ )
					for( int j = 0; j < n - w; j++ ){
						if( w + 1 < n && j + w + 1 < n ){
							S[i][j][w + 1][h] = S[i][j][w][h] + S[i][j + w + 1][0][h];
							
							if( S[i][j][w + 1][h] > max )
								max = S[i][j][w + 1][h];	
						}
						if( h + 1 < n && i + h + 1< n ){
							S[i][j][w][h + 1] = S[i][j][w][h] + S[i + h + 1][j][w][0];
											
							if( S[i][j][w][h + 1] > max )
								max = S[i][j][w][h + 1];
						}
					}

		std::printf("%i\n", max);
	}
}