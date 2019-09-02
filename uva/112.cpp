#include <cstdio>
#include <cctype>

bool found;

void skip() {
	char t;
	std::scanf(" %c", &t);
}

bool num(int* value) {
	int read = std::scanf(" %i", value);
	return ( read > 0 );
}
bool find_sum(int sum, int k){

	int value = 0;
	
	skip(); //l par	
	
	if( !num(&value) ){
		skip(); //r par
		return false; // empty tree
	}
	
	int node_val = value + k;
	
	bool lval = find_sum(sum, node_val);	
	bool rval = find_sum(sum, node_val);
	
	if( !lval  && !rval )
		if( node_val == sum )
			found = true;

	skip();

	return true;
}

int main(){
	int sum;
	
	while( std::scanf("%i", &sum) != EOF ){		
		found = false;
		find_sum(sum, 0);
		if( found )
			std::printf("yes\n");
		else
			std::printf("no\n");
	}
}
