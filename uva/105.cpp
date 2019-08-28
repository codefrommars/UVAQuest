#include <iostream>

int main(){
	int l, h, r;
	int len = 0, start = 10000; //---> Only for presentation.
	int sky[10000] = {};
	
	while( std::cin >> l ){
		std::cin >> h;
		std::cin >> r;
		
		for( int i = l; i < r; i++)
			if( sky[i] < h )
				sky[i] = h;
		
		if( r > len )
			len = r;
		
		if( l < start )
			start = l;
	}
	
	
	int currH = 0;

	for( int i = start; i <= len; i++ ){
		if( sky[i] != currH ){			
			currH = sky[i];
			 // Dumb presentation details.
			if( i > start )
				std::cout<< ' ';
			
			std::cout<< i << ' ' << currH;
		}		
	}	
	// Apparently this should be here.
	std::cout<< std::endl;
}