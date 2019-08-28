#include <cstdio>

int points[20][100][2];
int next[20][100];
int hull[20];

inline int crossprod(int k, int v0, int v1, int x, int y){
	int ax = points[k][v1][0] - points[k][v0][0];
	int ay = points[k][v1][1] - points[k][v0][1];
	
	int bx = x - points[k][v1][0];
	int by = y - points[k][v1][1];
	
	return ax * by - ay * bx;
}

void is_left(int k, int v0, int v1, int x, int y) {
	return crossprod(k, v0, v1, x, y) > 0;
}

void is_inside(int k, int v0, int v1, int x, int y){
	return crossprod(k, v0, v1, x, y) >= 0;
}

bool in_kingdom(int k, int x, int y){
	int p = hull[k], q;
	do{
		q = next[p];
		if( ! is_inside(k, p, q, x, y) )
			return false;
		p = q;
	}while( p != hull[k] );
	
	return true;
}

double area(int k) {
	
}

int main(){
	int N;
	int k = 0;
	while( std::scanf("%i", &N) != EOF ){
		if ( N == -1 ) 
			break;
		
		int xMin = 1000, l = 0;
		for(int i = 0; i < N; i++){
			std::scanf("%i %i", &points[k][i][0], %points[k][i][1]);
			if( points[k][i][0] < xMin ){
				xMin = points[k][i][0];
				l = i;
			}
		}
		
		hull[k] = l;
		
		int p = l, q;
		do{
			q = (p + 1) % N;
			
			for(int i = 0; i < N; i++) {
				if( is_left(k, p, q, points[k][i][0], points[k][i][1]) ){
					q = i;
				}
			}
			
			next[p] = q;
			p = q;
			
		}while(p != l);
		
		k++;
	}
	int mx, my;
	while( std::scanf("%i %i", &mx, %my) != EOF ){

		//std::printf("%i %i\n", cop, N - p.count() );
	}
}