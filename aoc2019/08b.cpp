#include <iostream>
#include <vector>

inline int digit(int* imgData, int W, int H, int L, int c, int r, int l){
    return imgData[l * (W * H) + r * W + c];
}

int countDigit(int* imgData, int W, int H, int L, int layer, int d){
    int z = 0;
    for( int c = 0; c < W; c++){
        for( int r = 0; r < H; r++){
            if( digit(imgData, W, H, L, c, r, layer) == d )
                z++;
        }
    }
    return z;
}

int main() {

    std::vector<int> img;
    
    char a = 0;

    while( std::cin >> a )
        img.push_back(a - '0');


    int W = 25;
    int H = 6;

    int L = img.size() / (W * H);
    
    int* data = &img[0];

    for( int r = 0; r < H; r++){
        for( int c = 0; c < W; c++){
            int l = 0;
            int p = 2;
            while( p == 2 && l < L){
                p = digit(data, W, H, L, c, r, l );
                l++;
            }
            if( p == 0 )
                std::cout << ' ';
            else
                std::cout << 'O';
        }
        std::cout << std::endl;
    }

}