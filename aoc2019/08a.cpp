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
    //std::cout << "Layers: " << L << std::endl;
    int minL = 0;
    int minZ = W * H + 1;
    for( int l = 0; l < L; l++){
        int z = countDigit(&img[0], W, H, L, l, 0);
        //std::cout << z << std::endl;
        if( z < minZ ){
            minZ = z;
            minL = l;
        }
    }


    int od = countDigit(&img[0], W, H, L, minL, 1);
    int td = countDigit(&img[0], W, H, L, minL, 2);

    std::cout << od * td << std::endl;

}