#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

std::map<std::string, int> people;
int parent[301];

int hier(int p, int* out){
	int len = 0;
	out[0] = p;	
	while( parent[p] != -1 ){
		p = parent[p];
		len++;
		out[len] = p;
	}
	
	return len;
}

void print_relation(int a, int b){
	//std::printf("parent[%i] -> %i , parent[%i] -> %i \n", a, parent[a], b, parent[b]);
	if( a == b ){
		std::printf("no relation\n");
		return;
	}
	
	if( parent[a] == parent[b] && parent[a] != -1 ){
		std::printf("sibling\n");
		return;
	}
	
	if( a == parent[b] ){
		std::printf("parent\n");
		return;
	}
	
	if( parent[b] != -1 && a == parent[parent[b]] ){ 
		std::printf("grand parent\n");
		return;
	}
	
	if( b == parent[a] ){
		std::printf("child\n");
		return;
	}
	
	if( parent[a] != -1 && b == parent[parent[a]] ){
		std::printf("grand child\n");
		return;
	}
	
	int ha[301], hb[301];
	int pa = hier(a, ha);		
	int pb = hier(b, hb);
	
	if( ha[pa] != hb[pb] ){
		std::printf("no relation\n");
		return;
	}		
	
	while( ha[pa] == hb[pb] ){
		
		if( pa == 0 ){ // it's a great grand parent
			for( int i = 2; i < pb; i++ )
				printf("great ");
			std::printf("grand parent\n");
			return;
		}
		
		if( pb == 0 ){ // it's a great grand child
			for( int i = 2; i < pa; i++ )
				printf("great ");
			std::printf("grand child\n");
			return;
		}
		
		pa--;
		pb--;
	}
	
	//pa is the hb[pa] is the last common ancestor
	
	
	
	//cousins
	int n = std::min(pa, pb);
	std::printf("%i cousin", n);
	
	int m = std::abs( pa - pb );
	if( m > 0 )
		std::printf(" removed %i", m);
	
	std::printf("\n");
}

int map_person(std::string name) {
	std::map<std::string, int>::iterator it = people.find(name);
	
	if( it != people.end() )
		return it->second;
		
	int key = people.size();
	people[name] = key;
	return key;
}

int main(){
	
	char cname[31], pname[31];
	std::fill_n(parent, 301, -1);
	
	while( std::scanf("%s %s", &cname[0], &pname[0]) != EOF ){
		if( strcmp(cname, "no.child") == 0 )
			break;
		
		int c = map_person(std::string(cname));
		int p = map_person(std::string(pname));
		parent[c] = p;		
		//std::printf("parent[%i] = %i\n", c, p);
	}
	
	
	
	while( std::scanf("%s %s", &cname[0], &pname[0]) != EOF ){
		int a = map_person(std::string(cname));
		int b = map_person(std::string(pname));
		
		print_relation(a, b);
		
		
		
	}
}
