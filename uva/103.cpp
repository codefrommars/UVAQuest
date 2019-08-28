#include <iostream>
#include <algorithm>
#include <vector>

int contained(int* a, int* b, int n){
	
	for(int i = 0; i < n; i++)
		if( a[i] >= b[i] )
			return 0;
	
	return 1;
}

std::vector<int> _lns(int boxes[][10], int k, int n, int j){
	
	std::vector<int> l;
	
	for( int i = 0; i < k; i++) {
		
		if( i == j )
			continue;
		
		if( contained( boxes[j], boxes[i], n ) ){
			std::vector<int> t = _lns(boxes, k, n, i);
			
			if( t.size() > l.size() )
				l = t;
		}
	}
	
	l.push_back( j );
	
	return l;	
}

int main(){
	
	int boxes[30][10];
	
	int k = 0;
	int n = 0;
	
	while( std::cin >> k ){
		std::cin >> n;
		for(int i = 0; i < k; i++ ){
			for(int j = 0; j < n; j++ )
				std::cin >> boxes[i][j];
			
			std::sort(boxes[i], boxes[i] + n);
		}
		
		std::vector<int> max_lns, curr;
			
		for(int j = 0; j < k; j++ ){
			curr = _lns(boxes, k, n, j);

			if( curr.size() >= max_lns.size() )
				max_lns = curr;
		}
		
		std::cout << max_lns.size() << std::endl;
		for(int j = max_lns.size() - 1; j  >= 0 ; j-- )
			std::cout << max_lns[j] + 1 << " ";
		
		std::cout << std::endl;
	}
}