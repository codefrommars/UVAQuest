#include <cstdio>

char v[] = "abcdefgh";

#define WHITE(x) std::printf("%.*s", (2 * (x)), "                                       ")

void print_comma(int n){
	for(int i = 0; i < n; i++){
		std::printf( "%c", v[i] );
		if( i != n - 1 )
			std::printf( ",");
	}
}

void print(int n) {
	std::printf( "writeln(" );
	for(int i = 0; i < n; i++){
		std::printf( "%c", v[i] );
		if( i != n - 1 )
			std::printf( ",");
	}
	std::printf( ")" );
	std::printf( "\n" );
}

void swap(int i, int j){
	char ci = v[i];
	v[i] = v[j];
	v[j] = ci;
}

void adv(int m, int n);

void orderm(int k, int m, int n){
	if( k == -1 ){
		std::printf("\n");
		adv(m + 1, n);
		return;
	}

	std::printf(" if %c < %c then\n", v[k], v[k + 1]);
	adv(m + 1, n);
	WHITE(m + 1);
	std::printf("else");
	swap(k, k + 1);
	orderm(k - 1, m, n);
	swap(k, k + 1);
}

void adv(int m, int n) {
	if( m == n - 1){
		WHITE(m + 1);
		print(n);
		return;
	}
	WHITE(m + 1);
	std::printf("if %c < %c then\n", v[m], v[m+1]);
	adv(m+1, n);
	WHITE(m + 1);
	std::printf("else");
	swap(m, m + 1);
	orderm(m-1, m, n);
	swap(m, m + 1);
}


void print_program(int n){
	std::printf("program sort(input,output);\nvar\n");
	print_comma(n);
	std::printf(" : integer;\nbegin\n");
	WHITE(1);
	std::printf("readln(");
	print_comma(n);
	std::printf(");\n");
	adv(0, n);
	std::printf("end.\n");
}

int main(){
	int M, N;
	std::scanf("%i", &M);
	for( int i = 0; i < M; i++ ){
		std::scanf("%i", &N);
		print_program(N);
		if( i != M - 1 )
			std::printf("\n");
	}	
}