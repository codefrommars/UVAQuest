//https://code.google.com/codejam/contest/32013/dashboard#s=p2

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>

double find_prob(double f, double R, double t, double r, double g) {
	const int M = 1000000;
	
	unsigned int hits_grid = 0;
	
	double gd = 2 * r + g;
	unsigned int hits_r = 0;
	
	for( int i = 0; i < M; i++){
		
		double u0 = static_cast<double>(std::rand()) / RAND_MAX;
		double u1 = static_cast<double>(std::rand()) / RAND_MAX;
		
		double fr = sqrt(u0) * R;
		
		if( R - fr < f + t ) {
			hits_r++;
			continue;
		}
		
		double ft = u1 * 0.5 * M_PI;
		
		double fx = fr * cos(ft);
		int dx = static_cast<int>( floor(fx / gd) );		
		
		if( (fx - dx * gd < f + r) || ( (dx + 1) * gd - fx < f + r) ){
			hits_grid++;
			continue;
		}
		
		double fy = fr * sin(ft);
		int dy = static_cast<int>( floor(fy / gd) );
		
		if( (fy - dy * gd < f + r) || ( (dy + 1) * gd - fy < f + r) ){
			hits_grid++;
			continue;
		}		
	}

	return static_cast<double>(hits_grid + hits_r) / M;
}

int main(){
	
	std::srand(time(NULL));

	int n;
	std::setbuf(stdout, NULL);
	
	std::scanf("%i", &n);
	
	for(int i = 0; i < n; i++){
		float f, R, t, r, g;		
		std::scanf("%f %f %f %f %f\n", &f, &R, &t, &r, &g);
		float p = find_prob(f, R, t, r, g);
		std::printf("Case #%i: %.6f\n", i + 1, p);
	}
	
}