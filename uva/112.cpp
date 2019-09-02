#include <cstdio>
#include <cctype>

bool next(int* value){	
	char c = getchar();
	while( c == ' ' || c == '\n' || c == '\t')
		c = getchar();
	
	//non whitespace
	if( c == '(' || c == ')' )
		return false;
	
	int sign = 1;
	
	//is it a sign?
	if ( c == '-' ){
		sign = -1;
		c = getchar();
	}
	int num = 0;
	//it's an integer.	
	while( isdigit(c) ){		
		num = num * 10 + (c - '0');	
		c = getchar();		
	}
	*value = sign * num;
	//std::printf("Read value: %i ungetting: '%c'(%i)\n", *value, c, c);
	ungetc(c, stdin);
	
	return true;
}
int find_sum(int sum, int k, int* found){

	int value = 0;	
	next(&value);	//"l par	
	if( !next(&value) )		
		return 0;
	
	int node_val = value + k;
	
	int lval = find_sum(sum, node_val, found);	
	int rval = find_sum(sum, node_val, found);
	
	if( lval == 0 && rval == 0 )
		if( node_val == sum )
			*found = 1;

	next(&value);

	return value;
}

int main(){
	int sum;
	int found;
	while( std::scanf("%i", &sum) != EOF ){		
		found = 0;
		find_sum(sum, 0, &found);
		if( found == 1 )
			std::printf("yes\n");
		else
			std::printf("no\n");
	}
}
