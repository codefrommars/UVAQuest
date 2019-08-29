#include <iostream>

#define MAX_LEN     100

int diff[MAX_LEN][MAX_LEN + 1] = {0};

// void printdiff(int n){
//     for( int i = 0; i < n; i++ ){
//         for( int j = 0; j < n; j++ ){
//             std::cout << diff[i][j] << ' ';
//         }
//         std::cout << std::endl;
//     }

// }

void clear(int n){
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ )
            diff[i][j] = 0;
}

int main(){
    int cases = 0;
    std::cin >> cases;
    
    for( int t = 0; t < cases; t++ ){
        int s= 0, c = 0;
        std::cin >> s; //len of the seq
        std::cin >> c; //ammount of numbers

        //Clear
        clear(s + c);

        for( int i = 0; i < s; i++ )
            std::cin >> diff[i][0];

        //Compute the differences
        for( int d = 1; d <= s + c; d++ )
            for( int i = 0; i < s - d; i++ )
                diff[i][d] = diff[i + 1][d - 1] - diff[i][d - 1];
        
        //fill the other parts
        for( int d = s - 1; d >= 0; d-- ){
            for( int i = 1; i < s + c; i++ ){
                diff[i][d] = diff[i - 1][d] + diff[i - 1][d + 1];
            }
        }

        //printdiff(s + c);

        for( int f = 0; f < c; f++){
            std::cout << diff[s + f][0] << ' ';
        }

        std::cout << std::endl;
    }

    return 0;
}
