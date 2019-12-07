#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define MAX 2000



int insert(std::map<std::string, int> &map, std::string k){
    if( map.count(k) == 0 )
        map[k] = map.size();
    return map[k];
}

int main(){
    char a[4], b[4];
    std::map<std::string, int> mapper;
    //std::vector<std::pair<int, int>> links;
    //int n = 0;
    //std::cout << "The matrix" << std::endl;
    int** orbit = new int*[MAX];
    for(int i = 0; i < MAX; i++){
        orbit[i] = new int[MAX];
            for( int j = 0; j < MAX; j++){
                orbit[i][j] = 0;
            }
    }
    while( scanf("%3s)%3s\n", &a, &b) != EOF ) {
        std::string sa(a);
        std::string sb(b);

        //std::cout << sa << "->"<< sb << std::endl;
        int f = insert(mapper, a);
        int t = insert(mapper, b);
        //std::cout << f << "->"<< t << std::endl;
        orbit[t][f] = 1;
        
    }
    
    std::cout << "Computing transitivity" << std::endl;
    for(int k = 0; k < MAX; k++){
        for(int i = 0; i < MAX; i++){
            for( int j = 0; j < MAX; j++){
                if( orbit[i][k] && orbit[k][j] )
                    orbit[i][j] = 1;
            }
        }
    }
    int count = 0;
    for(int i = 0; i < MAX; i++){
        for( int j = 0; j < MAX; j++){
            count += orbit[i][j];
        }
    }

    std::cout << count << std::endl;
    return 0;
}