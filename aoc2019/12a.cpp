#include <iostream>

// struct Vec {
//     int x;
//     int y;
//     int z;

//     int absSum() {
//         return std::abs(x) + std::abs(y) + std::abs(z);
//     }
// };

int absSum(int* v){
    return std::abs(v[0]) + std::abs(v[1]) + std::abs(v[2]);
}

int sgn(int a){
    if( a < 0 )
        return -1;
    if( a > 0 )
        return 1;
    return 0;
}

void simulate(int pos[4][3], int vel[4][3], int n){
    for(int i = 0; i < n; i++){
        for( int j = i + 1; j < n; j++){
                //Compute g
            int jx = sgn(pos[i][0] - pos[j][0]);
            int jy = sgn(pos[i][1] - pos[j][1]);
            int jz = sgn(pos[i][2] - pos[j][2]);

            vel[j][0] += jx; vel[i][0] -= jx; 
            vel[j][1] += jy; vel[i][1] -= jy; 
            vel[j][2] += jz; vel[i][2] -= jz; 
        }
    }

    for(int i = 0; i < n; i++){
        pos[i][0] += vel[i][0];
        pos[i][1] += vel[i][1];
        pos[i][2] += vel[i][2];
    }

}

int energy(int pos[4][3], int vel[4][3], int n){
    int totalE = 0;
    for(int i = 0; i < n; i++){
        int p = absSum(pos[i]);
        int k = absSum(vel[i]);
        totalE += p * k;
    }
    return totalE;
}

void print(int* p, int* v){
    std::cout << p[0] << ", " << p[1] << ", " << p[2] << " || " << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
}

void printS(int p[4][3], int v[4][3], int n){
    for(int i = 0; i < n; i++){
        print(p[i], v[i]);
    }
}

int main() {
    int pos[4][3] = {
        {3, 3, 0},
        {4, -16, 2},
        {-10, -6, 5},
        {-3, 0, -13}
    };
    // Vec pos[4] = {
    //     {-8, -10, 0},
    //     {5, 5, 10},
    //     {2, -7, 3},
    //     {9, -8, -3}
    // };

    int vel[4][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    for(long int i = 0; i < 1000; i++){
        simulate(pos, vel, 4);

    }
        //printS(pos, vel, 4);
    
    std::cout << energy(pos, vel, 4) << std::endl;

    return 0;
}