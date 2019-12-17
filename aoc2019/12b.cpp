#include <iostream>

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

void simulateAxis(int pos[4][3], int vel[4][3], int n, int index){
    for(int i = 0; i < n; i++){
        for( int j = i + 1; j < n; j++){
                //Compute g
            int g = sgn(pos[i][index] - pos[j][index]);

            vel[j][index] += g; vel[i][index] -= g; 
        }
    }

    for(int i = 0; i < n; i++){
        pos[i][index] += vel[i][index];
    }
}

void simulate(int pos[4][3], int vel[4][3], int n){
    for( int i = 0; i < 3; i++)
        simulateAxis(pos, vel, n, i);
}

long long cycle(int pos[4][3], int vel[4][3], int n, int index ){
    int ini[4] = {
        pos[0][index],
        pos[1][index],
        pos[2][index],
        pos[3][index],
    };

    long long count = 0;
    while( true ){
        simulateAxis(pos, vel, n, index);
        count++;

        if( vel[0][index] == 0 && vel[1][index] == 0 && vel[2][index] == 0 && vel[3][index] == 0 && 
            pos[0][index] == ini[0] && pos[1][index] == ini[1] && pos[2][index] == ini[2] && pos[3][index] == ini[3]){
                break;
        }
    }
    return count;
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

long long gcd(long long a, long long b){
    if( b == 0 )
        return a;
    
    return gcd(b, a % b );
}

long long lcm(long long a, long long b){
    return (a * b ) / gcd(a, b );
}

int main() {
    int pos[4][3] = {
        {3, 3, 0},
        {4, -16, 2},
        {-10, -6, 5},
        {-3, 0, -13}
    };

    // int pos[4][3] = {
    //     {-1, 0, 2},
    //     {2, -10, -7},
    //     {4, -8, 8},
    //     {3, 5, -1}
    // };

    // int pos[4][3] = {
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

    long long x = cycle(pos, vel, 4, 0);
    long long y = cycle(pos, vel, 4, 1);
    long long z = cycle(pos, vel, 4, 2);

    long long lxyz = lcm(lcm(x, y), z);
    std::cout << lxyz << std::endl;

    //long long lxyz = gcd(x,  gcd(y, z));
    
    //std::cout << (x / lxyz) * (y / lxyz) * (z / lxyz) / lxyz << std::endl;


    // for(long int i = 0; i < 1000; i++){
    //     simulate(pos, vel, 4);

    // }
        //printS(pos, vel, 4);
    
    // std::cout << energy(pos, vel, 4) << std::endl;

    return 0;
}