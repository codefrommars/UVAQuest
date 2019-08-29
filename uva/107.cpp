#include <cstdio>

inline unsigned int find_p(unsigned int h, unsigned int w, unsigned int n){
	unsigned int p = 0;
	unsigned int hp = 1;	
	unsigned int wp = 1;
	
	while( h != 1 ) {
		if( h % (n + 1) != 0 )
			return -1;
		
		h /= (n + 1);
		wp *= n;
		p++;
	}
	
	if( wp != w )
		return -1;
	
	return p;
}

inline void find_n(unsigned int h,  unsigned int w, unsigned int* out_n, unsigned int* out_p ){
	
	for( int n = 1; n < h; n ++ ){
		if( h % (n + 1) != 0 )
			continue;
		
		unsigned int r = h / (n + 1);
		
		unsigned int p = find_p(h, w, n);
		
		if( p != -1 ){
			*out_n = n;
			*out_p = p;
			return;
		}
		
		p = find_p(h, w, r);
		if( p != -1 ){
			*out_n = n;
			*out_p = r;
			return;
		}
	}
}

int main(){
	unsigned int h, w;
	unsigned int lazy, sum;
	
	std::setbuf(stdout, NULL);
	while( std::scanf("%i %i", &h, &w) != EOF ){
		if( h == 0 && w == 0)
			break;
		
		unsigned int n = 0, p = 0;
		find_n(h, w, &n, &p);
		
		unsigned int nw = 0;
		unsigned int sh = w;
		unsigned int ci = 1;
		
		for( int i = 0; i < p; i++) {
			nw += ci;
			sh += ci * h;
			h /= n + 1;
			ci *= n;
		}		
		std::printf("%u %u\n", nw, sh);
		
	}
}