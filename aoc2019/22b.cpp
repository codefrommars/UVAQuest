#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

inline __int64 pmod(__int64 value, __int64 mod){
    value = value % mod;
    
    if( value < 0 )
        value += mod;

    return value;
}

inline __int64 mult_mod(__int64 a, __int64 b, __int64 mod){
    __int64 p = 0;


    while( b > 0 ){
        if( b % 2 == 1 )
            p = pmod(p + a, mod);
        a = pmod(a * 2, mod);
        b = b / 2; 
    }

    return p;
}


// __int64 egcd(__int64 a, __int64 b, __int64 &x, __int64& y){
//     if( a == 0 ){
//         x = 0; 
//         y = 1;
//         return b;
//     }

//     __int64 x1, y1;
//     __int64 d = egcd( b % a, a, x1, y1);
//     x = y1 - (b / a) * x1;
//     y = x1;
//     return d;
// }

__int64 big_pow(__int64 a, __int64 n, __int64 m){
    if( n == 0 )
        return 1;
    if( n == 1 )
        return a;

    if( n % 2 == 0 ){
        __int64 p = big_pow(a, n >> 1, m);
        return mult_mod( p , p, m);
    }

    __int64 p = big_pow(a, (n - 1) >> 1, m);
    return mult_mod( mult_mod(a , p, m) , p, m);
    
    // __int64 q = (a * p) % m;
    // return (q * p) % m;
}

//m is prime
__int64 invMult(__int64 a, __int64 m){
    //a ^ ( m - 2) mod m
    return big_pow(a, m - 2, m);
}

void comp( __int64 &a, __int64 &b, __int64 c, __int64 d, __int64 m){
    __int64 at = mult_mod(a , c, m);
    __int64 bt =  pmod( mult_mod(b , c, m) + d, m);

    a = at;
    b = bt;
}

void fn_pow( __int64 &a, __int64 &b, __int64 m, __int64 n){

    if( n == 1 )
        return;

    if( n % 2 == 0 ){
        comp(a, b, a, b, m);        
        fn_pow( a, b, m, n >> 1);
    }else{        
        __int64 a1 = a;
        __int64 b1 = b;
        comp(a, b, a, b, m);
        fn_pow( a, b, m, (n - 1) >> 1);
        comp(a1, b1, a, b, m);
        a = a1;
        b = b1;
    }
}



int main(){
    
    std::string word;
    // constexpr __int64 N = 10007;
    // constexpr __int64 SHUFFLES = 1;
    // constexpr __int64 N = 1000700011;
    // constexpr __int64 SHUFFLES = 13;
    constexpr __int64 N = 119315717514047;
    constexpr __int64 SHUFFLES = 101741582076661;
    // constexpr __int64 SHUFFLES = 1;

    __int64 p = 2019;
    //__int64 q = 2020;

    __int64 a = 1;
    __int64 b = 0;

    // __int64 x = 1;
    // __int64 y = 0;



    while(std::cin >> word){
        if( word.compare("deal") == 0 ){
            std::cin >> word ; 
            if( word.compare("with") == 0 ){
                std::cin >> word ; // increment
                int inc;
                std::cin >> inc;
                // dealWI(inc);                
                a = mult_mod(a , inc, N);
                b = mult_mod(b , inc, N);
                continue;
            }

            if( word.compare("into") == 0 ){
                std::cin >> word ; // new
                std::cin >> word ; // stack
                // dealINS();
                a = pmod(-a, N);
                b = pmod(-b - 1, N);
                continue;
            }
        }

        if( word.compare("cut") == 0 ){
            int n;
            std::cin >> n;
            // cut(n);
            b = pmod(b - n, N);
        }
    }

    __int64 a0 = a;
    __int64 b0 = b;

    fn_pow(a0, b0, N, N - 1);
    std::cout << "base: " << a0 << " " <<  b0 << std::endl;


    std::cout << "fn: " << a << " " <<  b << std::endl;

    fn_pow(a, b, N, SHUFFLES);

    std::cout << "fn^k: " << a << " " <<  b << std::endl;
    
    __int64 ak = a;

    __int64 q = pmod( mult_mod(a , p, N) + b, N);

    std::cout << "q: " <<  q << std::endl;

    __int64 ia = pmod( invMult(a, N), N );

    std::cout <<"invA: " << ia << std::endl;

    __int64 one = mult_mod(ia , a, N);

    std::cout << "One: " << one << std::endl;
    
    //Invert
    fn_pow(a, b, N, N - 2);
    std::cout <<"Inverted: " << a << " " <<  b << std::endl;
    std::cout << "Other One: " << mult_mod(ak , a, N) << std::endl;


    __int64 iq = pmod( mult_mod(a , q, N) + b, N );
    
    std::cout << "iq: " <<  iq << std::endl;

    // __int64 q = (p * a + b) % N;
    // if( r < 0 )
    //     r += N;

    // // std::cout << r << std::endl;

    // std::cout << a << " " <<  b << std::endl;

    // __int64 a0 = a;
    // __int64 b0 = b;

    // std::cout << "Shuffling ... " << std::endl;
    // //Shuffles a lot of times.
    // fn_pow(a, b, N, SHUFFLES);

    // std::cout << a << " " <<  b << std::endl;

    // __int64 ak = big_pow(a0, SHUFFLES, N);
    // if( ak < 0 )
    //     ak += N;
    // std::cout << "ak: " << ak << std::endl;

    // std::cout << "Inverting ... " << std::endl;
    // __int64 invA = invMult(ak, N);
    // std::cout << invA * ak << std::endl;

    // __int64 p = ((q * invA) % N - (b * invA) % N) % N;

    // Computes the inverse
    //fn_pow(a, b, N, N - 2);
    //std::cout << a << " " <<  b << std::endl;

    // __int64 p = (q * a + b) % N;
    // if( p < 0 )
    //     p += N;

    // std::cout << p << std::endl;


    // __int64 ia = invMult(a, N);
    // if( ia < 0 )
    //     ia += N;

    // __int64 one = (a * ia) % N;
    // if( one < 0 )
    //     one += N;

    // std::cout << ia << std::endl;
    // std::cout << one << std::endl;
}

// constexpr __int64 N =           119315717514047; //10007;
// constexpr __int64 SHUFFLES =    101741582076661;

// __int64 p = 1510;

// struct Technique{
//     int code;
//     int param;
// };

// // 0
// __int64 invCut(__int64 q, __int64 c){
//     // if( c < 0 )
//     //     c += N;

//     return (q + c) % N;
// }
// // 1
// __int64 invINS(__int64 q){
//     return N - 1 - q;
// }
// //2


// __int64 egcd(__int64 a, __int64 b, __int64 &x, __int64& y){
//     if( a == 0 ){
//         x = 0; 
//         y = 1;
//         return b;
//     }

//     __int64 x1, y1;
//     __int64 d = egcd( b % a, a, x1, y1);
//     x = y1 - (b / a) * x1;
//     y = x1;
//     return d;
// }



// __int64 invDWI(__int64 q, __int64 a, __int64 n){
//     __int64 x0, y0;
//     __int64 g = egcd(a, n, x0, y0);

//     //solutions: 
//     __int64 sol = (x0 * q / g) % n;
//     if( sol < 0 )
//         sol += n;   
    
//     return sol;
// }

// __int64 findCard(std::vector<Technique> &shuffle, __int64 position){
//     __int64 q = position;
//     for(int i = shuffle.size() - 1; i >= 0; i--){
//         switch(shuffle[i].code){
//             case 0:
//                 q = invCut(q, shuffle[i].param);
//                 break;
//             case 1:
//                 q = invINS(q);
//                 break;
//             case 2:
//                 q = invDWI(q, shuffle[i].param, N);
//                 break;
//         }
//     }
//     return q;
// }

// __int64 findCycle(std::vector<Technique> &shuffle, __int64 position){
//     __int64 q = p;
//     __int64 i = 0;
//     do{
//         q = findCard(shuffle, q);
//         i++;
//     }while( q != position);

//     return i;
// }

// int main(){

//     //std::cout << invDWI(8, 5, 13) << std::endl;
//     //std::cout << (-13 % 7) << std::endl;

//     std::vector<Technique> shuffle;

//     std::string word;
//     while(std::cin >> word){
//         if( word.compare("deal") == 0 ){
//             std::cin >> word ; 
//             if( word.compare("with") == 0 ){
//                 std::cin >> word ; // increment
//                 int inc;
//                 std::cin >> inc;
//                 Technique dwi = {
//                     2,
//                     inc
//                 };
//                 shuffle.push_back(dwi);                
//                 continue;
//             }

//             if( word.compare("into") == 0 ){
//                 std::cin >> word ; // new
//                 std::cin >> word ; // stack                
//                 Technique dins = {
//                     1, -1
//                 };
//                 shuffle.push_back(dins);
//                 continue;
//             }
//         }

//         if( word.compare("cut") == 0 ){
//             int n;
//             std::cin >> n;
//             Technique c = {
//                 0, n
//             };
//             shuffle.push_back(c);            
//         }
//     }

    
//     //for( int q = 0; q < N; q++)
    
//     //std::cout << "Finding cycle..." << std::endl;
//     //__int64 cycle = findCycle(shuffle, p);
//     //std::cout << cycle << std::endl;

//     //__int64 rest = SHUFFLES % cycle;
//     // __int64 rest = 10;

//     // __int64 q = p;
//     // for( int i = 0; i < rest; i++){
//     //     __int64 next = findCard(shuffle, q);
//     //     std::cout << next << " " << q - next << std::endl;

//     //     q = next;
//     // }

//     std::cout << N - SHUFFLES - 1 << std::endl;
//     //std::cout << findCard(shuffle, p) << " ";
// }