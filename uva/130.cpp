#include <iostream>
#include <vector>

#define MAX 100

int values[MAX];
int next[MAX];

void print(std::vector<int> p){
    for(int i = 0; i < p.size(); i++){
        std::printf("%i ", p[i] );
    }
    std::printf("\n");
}

int advance(int* p, int k){
    int q;
    while( k > 1 ){
        q = *p;
        *p = next[*p];
        k--;
    }
    return q;
}

int remove(int pp){
    int p = next[pp];
    next[pp] = next[p];
    return p;
}

int insert(int pv, int v, int w){
    values[v] = values[w];
    int npv = next[pv];
    next[pv] = v;
    next[v] = npv;
    return npv;
}

int inline cut(int x, int mod){
    if( x < mod )
        return x;
    return x % mod;
}

int find_last(int n, int k){
    int p = k - 1, pv = k;

    while( n > 1 ){
        //int v = advance(p, k, -1);
        //Advance k        
        //kill
        int v = remove(pv);
        std::printf("remove %i\n", values[v]);
        advance(&p, 1);

        int pw = advance(&p, k);

        int w = remove(pw);

        p = insert(pv, v, w);
        pv = advance(&p, k);

        n--;
    }
    return values[next[p]];
}

int main() {


    int n, k;
    while( std::scanf("%i %i", &n, &k) != EOF ){
        if( n == 0 && k == 0 )
            break;        
        
        for(int i = 0; i < n; i++){
            values[i] = i + 1;
            next[i] = (i + 1) % n;
        }
        //int p = 0;
        //int pp = advance(&p, k);

        //std::printf("val[%i] = %i, pp = %i\n", p, values[p], pp );
        //print(v);
        std::printf("%i\n", find_last(n, k) );
    }

    return 0;
}