#include <iostream>

// - Use Floyd-Warshall to find the most profitable path in the graph 
// from every node to each other in 's' number of steps. Save the previous
// node in another matrix in order to find the path.
// - Go throught the solution matrix checking if the profit going
// from a node to itself is at least 1.01 in an increasing number of steps.

int main(){
	int n = 0;
	
read_input:
	while( std::cin >> n ){
		
		double ct[20][20][20] = {};
		int path[20][20][20] = {};
		
		//Build the input
		for(int i = 0; i < n; i++ ){			
			for(int j = 0; j < n; j++ ){
				path[i][j][0] = i;
				
				if( i == j )
					ct[i][j][0] = 1.0;
				else
					std::cin >> ct[i][j][0];
			}
		}
		
		//Run Floyd-Warshall
		for( int s = 1; s < n; s++ ){
			for(int k = 0; k < n; k++ ){
				for( int i = 0; i < n; i++){
					for(int j = 0; j < n; j++ ){						
						double p = ct[i][k][s - 1] * ct[k][j][0];
						
						if( p > ct[i][j][s] ){
							ct[i][j][s] = p;
							path[i][j][s] = k;
						}
						
					}
				}
			}
		}		
		
		//Find the solution
		for( int s = 1; s < n; s++ ){						
			for( int i = 0; i < n; i++){
				if( ct[i][i][s] > 1.01 ){
					//Profit larger than 1.01 in the smallest s
					int sol[s + 1];
					sol[s] = path[i][i][s];
					
					for( int j = s - 1; j >= 0; j--)
						sol[j] = path[i][ sol[j + 1] ][j];
					
					for(int j = 0; j <= s; j++)
						std::cout<< sol[j] + 1 << " ";
					
					std::cout << sol[0] + 1 << std::endl;
					
					//This is equivalent to a `break [label];` in java.
					goto read_input;
				}
			}
		}
		
		std::cout << "no arbitrage sequence exists\n";
	}
}