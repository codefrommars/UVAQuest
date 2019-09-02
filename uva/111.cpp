#include <cstdio>
#include <algorithm>

int rank[20 + 1];
int ans[20 + 1];

int seq[20 + 1];

int count(int N) {
	seq[1] = 1;
	int max_count = -1;
	for(int i = 2; i <= N; i++){
		int m = 0;
		for( int j = 1; j < i; j++)
			if( rank[ans[j]] < rank[ans[i]] )
				m = std::max(m, seq[j]);
		
		seq[i] = m + 1;
		if( seq[i] > max_count )
			max_count = seq[i];
	}
	
	return max_count;
}

int score() {
	return 0;
}

int process(int N){
	//Read rank
	int r = 0;
	for( int i = 1; i <= N; i++ ){
		std::scanf("%i", &rank[i]);
	}
		
	while(true){
		for( int i = 1; i <= N; i++ ){
			int ai = 0;
			if( std::scanf("%i", &ai) == EOF ) 
				return EOF;
				
			if( ai > N )
				return ai;
			
			ans[ai] = i;
				
			seq[i] = 0;
		}
		std::printf("%i\n", count(N));
	}
}

int main(){
	int N;
	
	std::scanf("%i", &N);
	
	while( N != EOF ){
		N = process(N);
	}
}