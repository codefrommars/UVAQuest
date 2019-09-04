#include <iostream>
#include <string>
#include <string.h>
#include <limits.h>

//Euler’s Path and Circuit Theorems

//A graph will contain an Euler path if it contains at most two vertices of odd degree.
//A graph will contain an Euler circuit if all vertices have even degree

//The problem specifies that "the number of intersections with odd degree in a postal route will be at most two" (zero or two)
//intersections with even degree can be visited on different streets each time (in and out), so it's possible to avoid
//revisiting streets. For intersections with odd degree at least one street has to be visited twice.

//The optimal route should start in an odd degree street, and the minimal cost is the cost of visiting each street
//once plus the cost of coming back from the other odd degree street.

#define N ('z' - 'a')

unsigned int c[N][N];
bool e[N][N];
int deg[N];

void reset(){
	for( int i = 0; i < N; i++){
		deg[i] = 0;
		for(int j = 0; j < N; j++){
			c[i][j] = INT_MAX;
			e[i][j] = false;
		}
	}
}

unsigned int cost(int a, int b){
	unsigned int d[N];
	for( int i = 0; i < N; i++)
		d[i] = INT_MAX;
	
	d[a] = 0;

	bool updated;
	for( int i = 0; i < N; i++){
		updated = false;
		//For each edge u -> v
		for( int u = 0; u < N; u++ ){
			for(int v = 0; v < N; v++ ){
				if( d[u] == INT_MAX || c[u][v] == INT_MAX )
					continue;

				if( d[u] + c[u][v] < d[v] ){
					updated = true;
					d[v] = d[u] + c[u][v];
				}
			}
		}
		if( !updated )
			break;
	}

	return d[b];
}

int back_cost() {
	int a = -1, b = -1;
	for( int i = 0; i < N; i++){
		if( deg[i] % 2 == 1 ){
			if( a == -1 )
				a = i;
			else
				b = i;
		}
	}

	if( a == -1 )
		return 0;
	
	return cost(a, b);
}

int main(){
	
	std::string street;

	reset();
	int cost = 0;	
	
	while( std::cin >> street ){
		
		if( street.compare("deadend")  == 0 ){
			std::cout << cost + back_cost() << std::endl;
			reset();
			cost = 0;
			continue;
		}

		int len = street.length();
		int s = street[0] - 'a';
		int t = street[len - 1] - 'a';
		//std::cout << street << " " << s << " -> " << t << " : " << len << std::endl;
		c[s][t] = len;
		c[t][s] = len;
		e[s][t] = true;
		e[t][s] = true;
		deg[s] ++;
		deg[t] ++;

		cost += len;
	}
}
