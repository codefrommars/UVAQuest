#include <iostream>
#include <string>
#include <string.h>
#include <limits.h>




//Euler’s Path and Circuit Theorems

//A graph will contain an Euler path if it contains at most two vertices of odd degree.
//A graph will contain an Euler circuit if all vertices have even degree

//The problem specifies that "the number of intersections with odd degree in a postal route will be at most two"
//So we already know there's an Euler Path

#define N ('z' - 'a')

int c[N][N];
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

int cost(int a, int b){
	if( e[a][b] )
		return c[a][b];
	
	// int vk = INT_MAX;
	// int mk = -1;
	// for( int k = 0; k < N; k++){
	// 	if( e[a][k] ){
	// 		int ck = c[a][k] + cost(k, b);
	// 	}
	// }
}

int back_cost() {
	int a = -1, b = -1;
	for( int i = 0; i < N; i++){
		if( deg[i] % 2 == 1 ){
			if( a == -1 )
				a = i;
			else
				b = 1;
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
		
		if( street.compare("deadend") ){
			std::cout << cost + back_cost();
			reset();
			cost = 0;
			continue;
		}

		int len = street.length();
		int s = street[0] - 'a';
		int t = street[len - 1];

		c[s][t] = len;
		c[t][s] = len;
		e[s][t] = true;
		e[t][s] = true;
		deg[s] ++;
		deg[t] ++;

		cost += len;
	}
}
